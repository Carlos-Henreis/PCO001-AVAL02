const jwt = require('jsonwebtoken');

const JWT_SECRET = process.env.JWT_SECRET;

function authenticate(user) {
    return jwt.sign({ matricula: user.matricula, nome: user.nome }, JWT_SECRET, { expiresIn: '1h' });
}

function verify(token) {
    try {
        return jwt.verify(token, JWT_SECRET);
    } catch (err) {
        return null;
    }
}

function verifyToken(req, res, next) {
    if (!/login|logout/i.test(req.originalUrl)) {
        const token = req.headers['authorization'];
        if (!token) {
            return res.status(403).json({ message: 'No token provided' });
        }
        const decoded = verify(token);
        if (!decoded) {
            return res.status(500).json({ message: 'Failed to authenticate token' });
        }
        req.user = decoded;
    }
    next();
}

module.exports = { authenticate, verify, verifyToken };
