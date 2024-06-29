const WebSocket = require('ws');
const { verify } = require('./auth');
const { broadcastOnlineUsers, addClient, removeClient, removeLoggedInUser, addLoggedInUser } = require('./broadcast');

async function setupWebSocket(server) {
    const wss = new WebSocket.Server({ server });

    wss.on('connection', async (ws, req) => {
        const urlParams = new URLSearchParams(req.url.split('?')[1]);
        const authQuery = urlParams.get('authorization');
        if (!authQuery) {
            console.error('Token de autenticação não fornecido');
            ws.close(1008, 'Token de autenticação não fornecido');
            return;
        }
        const decoded = verify(authQuery);
        ws.user = decoded;
        if (!decoded) {
            console.error('Token de autenticação inválido ou expirado');
            ws.close(1008, 'Token de autenticação inválido ou expirado');
            return;
        }
        console.log('Client connected');
        addClient(ws);
        addLoggedInUser(ws.user);
        broadcastOnlineUsers();

        ws.on('close', async () => {
            await removeLoggedInUser(ws);
            await removeClient(ws);
            console.log('Client disconnected');
            broadcastOnlineUsers();
        });
    });
}

module.exports = { setupWebSocket };