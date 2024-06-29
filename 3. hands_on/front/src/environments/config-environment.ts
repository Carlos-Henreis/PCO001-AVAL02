const fs = require('fs');
const dotenv = require('dotenv');

dotenv.config();

const envConfigFile = `export const environment = {
    httpServer: '${process.env["HTTP_SERVER"]}',	
    wsServer: '${process.env["WS_SERVER"]}',
};`;

fs.writeFileSync('./src/environments/environment.ts', envConfigFile);
fs.writeFileSync('./src/environments/environment.development.ts', envConfigFile);