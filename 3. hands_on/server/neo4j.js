const neo4j = require('neo4j-driver');

const URI = process.env.NEO4J_URI;
const USER = process.env.NEO4J_USER;
const PASSWORD = process.env.NEO4J_PASSWORD;

let driver = NaN;
let session = NaN;


function toNumber(integer) {
    if (neo4j.isInt(integer)) {
        return integer.toNumber();
    } else {
        return integer;
    }
}

async function open() {
    driver = neo4j.driver(URI, neo4j.auth.basic(USER, PASSWORD));
    session = await driver.session();
}

async function run(query, params) {
    try {
        const result = await session.run(query, params);
        return result;
    } catch (error) {
        console.error(error);
    }
}

async function close() {
    session.close();
    driver.close();
}

module.exports = { open, run, close, toNumber };