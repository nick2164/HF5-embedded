<?php
require_once "Devices.php";
require_once "Device.php";

class DeviceHandler
{

    private $fileName = 'devices.json';
    private $fileLocation;

    /**
     * This function checks if the json file, that holds the status of the devices exists. If it doesn't it will create it.
     * @return bool
     * @throws Exception
     */
    private function devicesFileHandler(): bool
    {

        $timestamp = new DateTime();

        if (!file_exists($this->fileLocation))
            file_put_contents($this->fileLocation, '{"lastUpdated":' . $timestamp->getTimestamp() . ',"devices":[]}');

        return true;

    }

    /**
     * This function will get devices json file.
     * @return mixed
     * @throws Exception
     */
    private function getDevicesFile()
    {
        if ($this->devicesFileHandler()) {
            return json_decode(file_get_contents($this->fileLocation));
        } else {
            die('Cannot get file.');
        }
    }

    public function __construct()
    {
        $this->fileLocation = __DIR__ . '/../' . $this->fileName;
    }

    /**
     * This function will check if a token is deemed valid.
     * @param string $token
     * @return bool
     * @throws Exception
     */
    public function checkIfTokenIsValid(string $token): bool
    {

        $timestamp = new DateTime();

        $fileContent = $this->getDevicesFile();

        /** @var Device $item */
        foreach ($fileContent->devices as $item) {
            if ($item->token == $token)
                if ($item->expireTime >= $timestamp->getTimestamp())
                    return true;

        }
        return false;

    }

    /**
     * This method will gather the device from the json file, and return a Device class.
     * @param string $token
     * @return Device
     * @throws Exception
     */
    public function getDeviceFromFile(string $token): Device
    {

        $timestamp = new DateTime();

        $fileContent = $this->getDevicesFile();

        /** @var Device $item */
        foreach ($fileContent->devices as &$item) {
            if ($item->token == $token)
                if ($item->expireTime >= $timestamp->getTimestamp()) {
                    $item->expireTime = $timestamp->modify('+1 hour')->getTimestamp();
                    return new Device($item->token, $item->expireTime, $item->rotateClockwise);
                }

        }
        throw new Exception("Device not found!", 400);

    }

    /**
     * @return Device
     * @throws Exception
     */
    public function insertNewDevice(): Device
    {
        $expireTime = new DateTime();
        $expireTime->modify('+1 hour');

        try {
            $newDevice = new Device(bin2hex(random_bytes(10)), $expireTime->getTimestamp());
        } catch (Exception $e) {
            die('LOL i failed to make random bytes!');
        }

        $this->appendDeviceFile($newDevice);

        return $newDevice;

    }

    /**
     * @param Device $newDevice
     * @throws Exception
     */
    public function appendDeviceFile(Device $newDevice): void
    {

        $deviceFile = $this->getDevicesFile();

        $timestamp = new DateTime();

        $deviceFile->lastUpdated = $timestamp->getTimestamp();

        array_push($deviceFile->devices, $newDevice);

        file_put_contents($this->fileLocation, json_encode($deviceFile));

    }

    /**
     * Returns all the devices in the Device file
     * @return array<Device>
     * @throws Exception
     */
    public function getDevicesFromFile(): array
    {
        return $this->getDevicesFile()->devices;
    }

    /**
     * Returns all the devices in the Device file
     * @return Devices
     * @throws Exception
     */
    public function getFile(): Devices
    {
        $file = $this->getDevicesFile();

        return new Devices($file->lastUpdated, $file->devices);
    }

    /**
     * @param string $token
     * @param bool $rotateClockwise
     * @return bool
     * @throws Exception
     */
    public function setDeviceRotateClockwise(string $token, bool $rotateClockwise): bool
    {

        $timestamp = new DateTime();

        $fileContent = $this->getDevicesFile();

        /** @var Device $item */
        foreach ($fileContent->devices as &$item) {
            if ($item->token == $token)
                if ($item->expireTime >= $timestamp->getTimestamp()) {
                    $item->rotateClockwise = $rotateClockwise;
                    $item->expireTime = $timestamp->modify('+1 hour')->getTimestamp();
                    break;
                }
        }
        return file_put_contents($this->fileLocation, json_encode($fileContent));

    }

}