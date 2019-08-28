<?php
class Device
{

    public function __construct(string $token, int $expireTime, bool $rotateClockwise = true)
    {

        $this->token = $token;
        $this->expireTime = $expireTime;
        $this->rotateClockwise = $rotateClockwise;

    }

    /** @var string $token */
    public $token;

    /** @var int $expireTime */
    public $expireTime;

    /** @var bool $rotateClockwise */
    public $rotateClockwise;

}