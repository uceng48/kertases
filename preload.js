const { contextBridge, ipcRenderer } = require('electron');
const fs = require('fs');
const path = require('path');

contextBridge.exposeInMainWorld('electronAPI', {
    getLocalIp: () => ipcRenderer.invoke('get-local-ip'),
    // Fitur baca folder img secara otomatis
    readImgFolder: () => {
        const dirPath = path.join(__dirname, 'img');
        try {
            return fs.readdirSync(dirPath).filter(file => /\.(png|jpe?g|svg)$/i.test(file));
        } catch (e) {
            return [];
        }
    }
});