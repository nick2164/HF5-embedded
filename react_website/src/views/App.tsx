import React from 'react';
import './App.css';
import {Table} from 'react-bootstrap';
import Devices from "../components/Devices";

const App: React.FC = () => {

    return (
        <div className="App">
            <header className="App-header">
                <Table striped bordered hover>
                    <thead>
                    <tr>
                        <th>ID</th>
                        <th>Gyldig til og med</th>
                        <th>Rotere med uret?</th>
                    </tr>
                    </thead>
                    <tbody>
                    <Devices/>
                    </tbody>
                </Table>

            </header>
        </div>
    );
};

export default App;
