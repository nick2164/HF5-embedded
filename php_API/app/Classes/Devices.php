<?php


class Devices
{

    public function __construct(int $lastUpdated, array $devices)
    {
        $this->lastUpdated = $lastUpdated;
        $this->devices = $devices;
    }

    /** @var int $lastUpdated */
    public $lastUpdated;

    /** @var array<Device> $devices */
    public $devices;

}