const WebSocket = require('ws');
let clients = [];
let users_logged_in = [];

function broadcast(data) {
    clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(data));
        }
    });
}

function broadcastOnlineUsers() {
    broadcast({ type: 'USERS_LOGGED_IN', users_logged_in });
}

function addLoggedInUser(user) {
    if (!users_logged_in.some(u => u.matricula === user.matricula)) {
        users_logged_in.push(user);
    }
}  

async function removeLoggedInUser(ws) {
    // Remove user from users_logged_in IF EXISTS ONLY ONE CLIENT WITH THE SAME MATRICULA
    const user = await users_logged_in.find(async u => u.matricula === ws.user.matricula);
    if (!user) return;
    
    const userClients = clients.filter(async client => client.user.matricula === ws.user.matricula);
    if (userClients.length === 1) {
        users_logged_in = users_logged_in.filter(u => u.matricula !== ws.user.matricula);
    }
}

async function removeClient(ws) {
    clients = clients.filter(async client => client !== ws);
    console.log('total de clientes conectados: ', clients.length);
}

async function addClient(ws) {
    await clients.push(ws);
    console.log('total de clientes conectados: ', clients.length);
}

module.exports = { 
    broadcast,
    broadcastOnlineUsers, 
    addLoggedInUser, 
    removeLoggedInUser ,
    addClient,
    removeClient
};
