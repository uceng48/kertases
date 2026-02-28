const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');
const { PeerServer } = require('peer');
const os = require('os');

// 1. Setup Local Peer Server (Port 9000)
// Ini membuat aplikasi Anda menjadi SERVER saat dijalankan
const peerServer = PeerServer({ port: 9000, path: '/Think' });

let mainWindow;

function createWindow() {
    mainWindow = new BrowserWindow({
        width: 1280,
        height: 800,
        icon: path.join(__dirname, 'icon.png'), // Opsional
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
	// PENTING: Matikan sandbox agar bisa require('fs') di preload
            sandbox: false, 
            nodeIntegration: false, // Security best practice
            contextIsolation: true,
            webSecurity: false // Izinkan memuat gambar lokal (img/)
        }
    });

    mainWindow.loadFile('index.html');
}

// 2. Helper: Dapatkan IP Address Lokal komputer ini
// Agar user tahu IP mereka untuk diberikan ke partner
ipcMain.handle('get-local-ip', () => {
    const interfaces = os.networkInterfaces();
    for (const name of Object.keys(interfaces)) {
        for (const iface of interfaces[name]) {
            if (iface.family === 'IPv4' && !iface.internal) {
                return iface.address;
            }
        }
    }
    return '127.0.0.1';
});

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') app.quit();
});
