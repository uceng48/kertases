const { app, BrowserWindow, ipcMain } = require('electron');
const { PeerServer } = require('peer');
const path = require('path');

// Fungsi kanggo nangtoskeun lokasi file (Audio/Icon)
// Upami tos jadi .exe, file aya dina folder 'resources/build'
function getAssetPath(relativePath) {
    return app.isPackaged 
        ? path.join(process.resourcesPath, 'build', relativePath)
        : path.join(__dirname, 'build', relativePath);
}

// Jalankeun Server Peer Lokal
try {
    PeerServer({ port: 9000, path: '/kertases-app' });
    console.log("Server PeerJS jalan dina port 9000");
} catch (e) { 
    console.log("Server parantos jalan atanapi aya masalah."); 
}

function createWindow() {
  const win = new BrowserWindow({
    width: 1280,
    height: 800,
    title: "Kertases Pro V14.2",
    icon: getAssetPath('icon.ico'), // Lokasi icon anu leres
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false
    }
  });
// Di main.js, setelah createWindow()

// Handler untuk request focus dari renderer
ipcMain.on('request-focus', (event) => {
    const win = BrowserWindow.fromWebContents(event.sender);
    if (win) {
        win.focus();
        win.show();
        
        // Juga force focus ke webContents
        win.webContents.focus();
        
        console.log("Focus requested from renderer");
    }
});

  win.setMenuBarVisibility(false);
  win.loadFile('index.html');

  // Ngirim informasi path audio ka renderer (index.html) upami diperyogikeun
  win.webContents.on('did-finish-load', () => {
    win.webContents.send('audio-path', {
        notif: getAssetPath('notif.mp3'), // ganti ku ngaran file audio anjeun
        done: getAssetPath('done.mp3')
    });
  });
}

app.whenReady().then(createWindow);

app.on('window-all-closed', () => { 
    if (process.platform !== 'darwin') app.quit(); 
});