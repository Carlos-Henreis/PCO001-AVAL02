const express = require('express');
const { v4: uuidv4 } = require('uuid');
const { authenticate } = require('./auth');
const { toNumber, open, run, close } = require('./neo4j');
const { broadcast, broadcastOnlineUsers, addLoggedInUser, removeLoggedInUser } = require('./broadcast');

const router = express.Router();

router.post('/login', async (req, res) => {
    try {
        const { matricula } = req.body;
        await open()
        const result = await run('MATCH (u:User {matricula: $matricula}) RETURN u', { matricula });
        if (result.records.length === 0) {
            res.status(401).json({ message: 'Usuário não encontrado' });
        } else {
            const user = result.records[0].get('u').properties;
            const token = authenticate(user);
            if (!token) {
                res.status(401).json({ message: 'Erro ao gerar token' });
            } else {
                res.json({ token });
            }
            addLoggedInUser(user);
            broadcastOnlineUsers();
            close();
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

router.post('/logout', async (req, res) => {
    try {
        const { matricula } = req.body;
        await open();
        const result = await run('MATCH (u:User {matricula: $matricula}) RETURN u', { matricula });
        if (result.records.length === 0) {
            res.status(401).json({ message: 'Usuário não encontrado' });
        } else {
            broadcastOnlineUsers();
            user = result.records[0].get('u').properties;
            res.json(user);
        }
        close();
    } catch (error) {
        console.error(error);
        res.status(500).json({ error: error.message });
    }
});

router.post('/posts', async (req, res) => {
    const { userId, content } = req.body;
    try {
        const postId = uuidv4();
        await open();
        await run('MATCH (u:User {matricula: $userId}) CREATE (u)-[:POSTADO]->(p:Post {id: $postId, content: $content, timestamp: timestamp()}) RETURN p', { userId, content, postId });
        close();

        await open();
        const result_consulta = await run('MATCH (u:User)-[:POSTADO]->(p:Post {id: $postId}) OPTIONAL MATCH (p)<-[l:LIKES]-() RETURN p, u.nome AS nome, COUNT(l) AS likes', { postId });
        const post = result_consulta.records[0].get('p').properties;
        post.user = result_consulta.records[0].get('nome');
        post.likes = toNumber(result_consulta.records[0].get('likes'));
        post.timestamp = toNumber(post.timestamp);
        broadcast({ type: 'NEW_POST', post });
        res.json(post);
        close();
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

router.get('/posts', async (req, res) => {
    try {
        await open();
        const result = await run('MATCH (u:User)-[:POSTADO]->(p:Post) OPTIONAL MATCH (p)<-[l:LIKES]-() RETURN p, u.nome AS nome, COUNT(l) AS likes ORDER BY p.timestamp DESC');
        const posts = result.records.map(record => {
            const post = record.get('p').properties;
            post.user = record.get('nome');
            post.likes = toNumber(record.get('likes'));
            post.timestamp = toNumber(post.timestamp);
            return post;
        });
        res.json(posts);
        close();
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

router.post('/posts/:postId/like', async (req, res) => {
    try {
        const { postId } = req.params;
        const { userId } = req.body;
        await open();
        await run('MATCH (u:User {matricula: $userId}), (p:Post {id: $postId}) CREATE (u)-[:LIKES]->(p) RETURN p', { userId, postId });
        broadcast({ type: 'LIKE_POST', postId });
        res.json({ message: 'Post liked successfully' });
        close();
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

module.exports = router;