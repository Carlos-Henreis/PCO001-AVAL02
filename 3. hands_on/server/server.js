require('dotenv').config();
const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const http = require('http');
const { verifyToken } = require('./auth');
const routes = require('./routes');
const { setupWebSocket } = require('./websocket');

const app = express();
app.use(cors());
app.use(bodyParser.json());

app.use('/api', verifyToken, routes);

const server = http.createServer(app);

setupWebSocket(server);

server.listen(3000, () => {
    console.log('Server running on port 3000');
});