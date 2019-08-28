import React, {useEffect, useState} from 'react';
import axios from 'axios';
import Device, {DeviceAPIResponse} from "./Device";
import moment from "moment";

interface DevicesAPIResponse {
    expireTime: number,
    devices: DeviceAPIResponse[]
}

const placeholderData: DevicesAPIResponse = {
    devices: [],
    expireTime: 0
};

const Devices = () => {

    const [fetchedData, setFetchedData] = useState(placeholderData);
    const [isLoading, setIsLoading] = useState(true);

    useEffect(() => {
        axios.get(`http://10.142.66.159:8080/devices`).then(function (response) {
                setFetchedData(response.data);
                setIsLoading(false);
            }
        );
    },[]);

    return (
        <React.Fragment>
            {
                (isLoading) ? (<p>Loading...</p>) : (
                    fetchedData.devices.map(value =>
                            (value.expireTime >= moment().unix()) ?
                        (<Device token={value.token}/>) : (null)
                    )
                )
            }
        </React.Fragment>

    )
};

export default Devices;