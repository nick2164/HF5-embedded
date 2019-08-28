<?php

use Psr\Http\Message\ResponseInterface as Response;
use Psr\Http\Message\ServerRequestInterface as Request;
use Slim\Factory\AppFactory;

require_once __DIR__ . '/Classes/DeviceHandler.php';

require __DIR__ . '/../vendor/autoload.php';

$app = AppFactory::create();

$app->get('/', function (Request $request, Response $response, $args) {
    $response->getBody()->write(file_get_contents(__DIR__ . '/website/src/index.tsx'));
    return $response;
});

$app->patch('/device/{id}', function (Request $request, Response $response, $args) {
    if (!$args['id'])
        return $response->withStatus(400);

    $deviceHandler = new DeviceHandler();

    if (!$deviceHandler->checkIfTokenIsValid($args['id']))
        return $response->withStatus(403);

    /** @var Device $parsedRequest */
    $parsedRequest = json_decode($request->getBody()->getContents());

    if (!is_bool($parsedRequest->rotateClockwise))
        return $response->withStatus(400);

    if (isset($parsedRequest->rotateClockwise)) {
        if ($deviceHandler->setDeviceRotateClockwise($args['id'], $parsedRequest->rotateClockwise)) {
            return $response->withStatus(204);
        } else {
            return $response->withStatus(400);
        }
    } else {
        return $response->withStatus(400);
    }

});

$app->get('/device/{id}', function (Request $request, Response $response, $args) {
    if (!$args['id'])
        return $response->withStatus(400);

    $deviceHandler = new DeviceHandler();;


    if (!$deviceHandler->checkIfTokenIsValid($args['id']))
        return $response->withStatus(403);

    $response->getBody()->write(json_encode($deviceHandler->getDeviceFromFile($args['id'])));
    return $response->withHeader('Content-Type', 'application/json')->
    withHeader('Access-Control-Allow-Headers', "Origin, X-Requested-With, Content-Type, Accept")->
    withHeader('Access-Control-Allow-Origin', "*");
});

$app->options('/devices', function (Request $request, Response $response) {
    return $response->
    withHeader('Access-Control-Allow-Methods', "OPTIONS, GET")->
    withHeader('Access-Control-Allow-Headers', "Content-Type")->
    withHeader('Access-Control-Allow-Origin', "*")->
    withStatus(204);
});

$app->get('/devices', function (Request $request, Response $response) {
    $deviceHandler = new DeviceHandler();

    $response->getBody()->write(json_encode($deviceHandler->getFile()));
    return $response->
    withHeader('Access-Control-Allow-Origin', "*")->
    withHeader('Content-Type', 'application/json');
});

$app->options('/token', function (Request $request, Response $response) {
    return $response->
    withHeader('Access-Control-Allow-Methods', "OPTIONS, POST")->
    withHeader('Access-Control-Allow-Headers', "Content-Type")->
    withHeader('Access-Control-Allow-Origin', "*")->
    withStatus(204);
});

$app->post('/token', function (Request $request, Response $response) {

    $jsonData = json_decode($request->getBody()->getContents());

    if (!isset($jsonData->identifier))
        return $response->withStatus(400);

    if ($jsonData->identifier != 'LOL')
        return $response->withStatus(403);

    $deviceHandler = new DeviceHandler();
    $newDevice = $deviceHandler->insertNewDevice();
    $response->getBody()->write(json_encode($newDevice));

    return $response;
});

$app->run();
