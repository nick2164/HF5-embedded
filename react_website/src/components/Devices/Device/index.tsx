import React, {useEffect, useState} from 'react';
import axios from "axios";
import moment from "moment";

interface Device {
    token: string
}

export interface DeviceAPIResponse {
    token: string,
    expireTime: number,
    rotateClockwise: boolean
}

const placeholderData: DeviceAPIResponse = {
    token: 'LOLs',
    expireTime: 0,
    rotateClockwise: true
};

const Device = (props: Device) => {

    const [fetchedData, setFetchedData] = useState(placeholderData);
    const [isLoading, setIsLoading] = useState(false);
    const [error, setError] = useState(false);

    useEffect(() => {
        setInterval(() => {
            setIsLoading(true);
            axios.get(`http://10.142.66.159:8080/device/${props.token}`).then(response => {
                    setFetchedData(response.data);
                    setIsLoading(false);
                }
            ).catch(reason => {
                setIsLoading(false);
                setError(true);
            });
        },4000); // TODO: There is a problem with this being called exponentially.

    });

    return (
        <React.Fragment>
            {
                (isLoading) ? (<p>Loading...</p>) :
                    (
                        <React.Fragment>
                            {
                                (error) ? (<tr>Error!</tr>) : (
                                    <tr>
                                        <td>{props.token}</td>
                                        <td>{moment(fetchedData.expireTime).format('MMMM Do YYYY, h:mm:ss a')}</td>
                                        <td>{(fetchedData.rotateClockwise) ? (<p>Ja</p>) : (<p>Nej</p>)}</td>
                                    </tr>
                                )
                            }

                        </React.Fragment>
                    )
            }
        </React.Fragment>

    );

};

export default Device;