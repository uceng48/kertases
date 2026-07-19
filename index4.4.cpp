<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Think Flow · Web Edition</title>

    <!-- CDN lokal / eksternal -->
    <script src="libs/peerjs.min.js"></script>
    <script src="libs/pdf.min.js"></script>
    <script src="libs/jspdf.umd.min.js"></script>
    <script src="libs/jspdf.plugin.autotable.min.js"></script>
    <!-- Fonts -->
    <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@300;400;600;700&family=Inter:wght@300;400;500;600;700&family=Roboto+Mono&display=swap" rel="stylesheet">

    <style>
        /* ========== FACEBOOK GLOBAL DESIGN TOKENS ========== */
        :root {
            --fb-blue: #1877f2;
            --fb-blue-hover: #166fe5;
            --fb-bg: #f0f2f5;
            --fb-card: #ffffff;
            --fb-text: #050505;
            --fb-text-dim: #65676b;
            --fb-border: #ced0d4;
            --fb-input: #f0f2f5;
            --fb-hover: #e4e6eb;
            --success: #42b72a;
            --danger: #f02849;
            --warning: #f59e0b;
            --shadow: 0 1px 2px rgba(0, 0, 0, 0.1), 0 2px 4px rgba(0, 0, 0, 0.1);
        }

        * { box-sizing: border-box; outline: none; }
        body, html {
            margin: 0; padding: 0;
            font-family: 'Inter', 'Segoe UI', Helvetica, Arial, sans-serif;
            background: var(--fb-bg);
            color: var(--fb-text);
            height: 100vh;
            overflow: hidden;
        }

        ::-webkit-scrollbar { width: 8px; height: 8px; }
        ::-webkit-scrollbar-track { background: transparent; }
        ::-webkit-scrollbar-thumb { background: var(--fb-border); border-radius: 10px; }
        ::-webkit-scrollbar-thumb:hover { background: var(--fb-text-dim); }

        /* General Flat Card Styles */
        .fb-card-panel {
            background: var(--fb-card);
            border-radius: 8px;
            box-shadow: var(--shadow);
            border: 1px solid rgba(0, 0, 0, 0.08);
            margin-bottom: 16px;
            padding: 12px 16px;
        }

        .fb-input {
            background: var(--fb-input);
            border: none;
            border-radius: 20px;
            color: var(--fb-text);
            padding: 10px 16px;
            font-size: 0.9rem;
            width: 100%;
            transition: background 0.2s;
        }
        .fb-input:focus {
            background: #e4e6eb;
        }

        .btn {
            border-radius: 6px;
            border: none;
            padding: 8px 16px;
            cursor: pointer;
            font-weight: 600;
            font-size: 0.85rem;
            display: inline-flex;
            align-items: center;
            gap: 6px;
            justify-content: center;
            transition: background 0.2s, transform 0.1s;
        }
        .btn-primary { background: var(--fb-blue); color: white; }
        .btn-primary:hover { background: var(--fb-blue-hover); }
        .btn-success { background: var(--success); color: white; }
        .btn-danger { background: var(--danger); color: white; }
        .btn-outline { background: var(--fb-input); color: var(--fb-text); }
        .btn-outline:hover { background: var(--fb-hover); }
        .btn-mini { padding: 4px 10px; font-size: 0.75rem; border-radius: 4px; }

        /* ========== ROLE-BASED TAILORED VISIBILITIES ========== */
        .role-admin-only, .role-designer-only, .role-operator-only { display: none !important; }
        
        body.role-admin .role-admin-only { display: block !important; }
        body.role-admin .role-admin-flex { display: flex !important; }
        
        body.role-designer .role-designer-only { display: block !important; }
        body.role-designer .role-designer-flex { display: flex !important; }
        
        body.role-operator .role-operator-only { display: block !important; }
        body.role-operator .role-operator-flex { display: flex !important; }

        /* Login Screen */
        #login-screen {
            position: fixed; inset: 0; z-index: 1000;
            display: flex; flex-direction: column; align-items: center; justify-content: center;
            background: var(--fb-bg);
        }
        .login-header-logo {
            font-family: 'Outfit', sans-serif;
            font-size: 3rem;
            font-weight: 700;
            color: var(--fb-blue);
            margin-bottom: 8px;
            letter-spacing: -1px;
        }
        .login-box {
            padding: 24px; max-width: 400px; width: 90%;
            background: var(--fb-card); border-radius: 8px; box-shadow: var(--shadow);
            text-align: center;
        }
        .role-grid {
            display: flex; flex-direction: column; gap: 10px; margin-top: 20px;
        }
        .role-card {
            padding: 12px; border: 1px solid var(--fb-border); border-radius: 8px;
            cursor: pointer; background: var(--fb-card); transition: background 0.2s;
            display: flex; align-items: center; gap: 12px; font-weight: 600;
        }
        .role-card:hover {
            background: var(--fb-hover);
        }
        .role-card i { font-size: 1.5rem; }

        /* ========== APP HEADER (FACEBOOK TOP BAR) ========== */
        #fb-top-bar {
            position: fixed; top: 0; left: 0; right: 0; height: 56px;
            background: var(--fb-card); box-shadow: var(--shadow);
            display: flex; align-items: center; justify-content: space-between;
            padding: 0 16px; z-index: 900;
        }
        .top-left { display: flex; align-items: center; gap: 8px; }
        .top-logo {
            width: 40px; height: 40px; background: var(--fb-blue);
            border-radius: 50%; display: flex; align-items: center; justify-content: center;
            color: white; font-family: 'Outfit', sans-serif; font-size: 1.6rem; font-weight: 800;
        }
        .top-logo-text {
            font-family: 'Outfit', sans-serif; font-size: 1.4rem; font-weight: 700; color: var(--fb-blue);
            letter-spacing: -0.5px; margin-right: 12px;
        }
        .top-search-container { position: relative; width: 240px; }
        .top-search-container input { height: 40px; padding-left: 36px; }
        .top-search-container i { position: absolute; left: 12px; top: 12px; color: var(--fb-text-dim); }

        .top-middle-tabs { display: flex; height: 100%; align-items: center; gap: 4px; }
        .nav-tab {
            height: 100%; padding: 0 24px; display: flex; align-items: center;
            justify-content: center; cursor: pointer; border-bottom: 3px solid transparent;
            color: var(--fb-text-dim); font-size: 1.4rem; transition: color 0.2s;
        }
        .nav-tab:hover { background: var(--fb-hover); border-radius: 8px; margin: 4px 0; height: calc(100% - 8px); }
        .nav-tab.active { border-bottom-color: var(--fb-blue); color: var(--fb-blue); }

        .top-right { display: flex; align-items: center; gap: 8px; }
        .profile-badge {
            display: flex; align-items: center; gap: 8px; padding: 4px 12px;
            border-radius: 20px; background: var(--fb-hover); font-weight: 600; font-size: 0.85rem;
        }
        .avatar-circle {
            width: 28px; height: 28px; border-radius: 50%; background: var(--fb-blue);
            color: white; display: flex; align-items: center; justify-content: center;
            font-weight: bold; font-size: 0.8rem;
        }

        /* ========== APP LAYOUT ========== */
        #app-layout {
            display: none; padding-top: 56px; height: 100vh;
            grid-template-columns: 280px 1fr 340px; background: var(--fb-bg);
        }
        .sidebar-left {
            padding: 16px; overflow-y: auto; display: flex; flex-direction: column; gap: 16px;
        }
        .feed-container {
            padding: 16px; overflow-y: auto; display: flex; flex-direction: column; gap: 16px;
            max-width: 680px; margin: 0 auto; width: 100%;
        }
        .sidebar-right {
            padding: 16px; overflow-y: auto; display: flex; flex-direction: column; gap: 16px;
            border-left: 1px solid rgba(0, 0, 0, 0.05);
        }

        /* Composer Box (What's on your mind?) */
        .composer-box {
            padding: 12px 16px; background: var(--fb-card); border-radius: 8px; box-shadow: var(--shadow);
        }
        .composer-header { display: flex; gap: 8px; margin-bottom: 12px; }
        .composer-trigger {
            background: var(--fb-input); border-radius: 20px; flex: 1; display: flex;
            align-items: center; padding: 0 16px; color: var(--fb-text-dim); cursor: pointer;
            font-size: 0.9rem; border: none; height: 40px; text-align: left;
        }
        .composer-trigger:hover { background: var(--fb-hover); }
        .composer-options {
            display: flex; justify-content: space-around; border-top: 1px solid var(--fb-border);
            padding-top: 8px; font-size: 0.85rem; color: var(--fb-text-dim); font-weight: 600;
        }
        .comp-opt { display: flex; align-items: center; gap: 6px; cursor: pointer; padding: 6px 12px; border-radius: 6px; }
        .comp-opt:hover { background: var(--fb-hover); }

        /* Timeline Post / Feed Card */
        .msg-card {
            background: var(--fb-card); border-radius: 8px; box-shadow: var(--shadow);
            border: 1px solid rgba(0, 0, 0, 0.08); margin-bottom: 16px; overflow: hidden;
        }
        .msg-card.selected { border: 2px solid var(--fb-blue); }
        .msg-header {
            padding: 12px 16px; display: flex; align-items: center; justify-content: space-between;
        }
        .poster-info { display: flex; align-items: center; gap: 10px; }
        .poster-meta { display: flex; flex-direction: column; }
        .poster-name { font-weight: 700; font-size: 0.9rem; }
        .poster-sub { font-size: 0.75rem; color: var(--fb-text-dim); display: flex; align-items: center; gap: 4px; }
        
        .msg-body { padding: 4px 16px 12px 16px; font-size: 0.9rem; }
        .msg-body-caption { margin-bottom: 8px; white-space: pre-wrap; line-height: 1.4; }

        .asset-attachment-container {
            border: 1px solid var(--fb-border); border-radius: 8px; overflow: hidden;
            background: #000; display: flex; flex-direction: column; align-items: center;
            max-height: 350px; justify-content: center; position: relative;
        }
        .asset-attachment-container img { max-width: 100%; max-height: 350px; object-fit: contain; }

        .msg-footer {
            border-top: 1px solid var(--fb-border); padding: 4px 8px;
            display: flex; justify-content: space-between; background: var(--fb-card);
        }
        .msg-footer .btn { flex: 1; border-radius: 4px; background: transparent; color: var(--fb-text-dim); }
        .msg-footer .btn:hover { background: var(--fb-hover); color: var(--fb-text); }

        /* Badges */
        .fb-badge {
            font-size: 0.7rem; font-weight: bold; padding: 2px 8px; border-radius: 12px; display: inline-block;
        }
        .fb-badge-success { background: #e7f3e8; color: var(--success); }
        .fb-badge-warning { background: #fef3c7; color: var(--warning); }
        .fb-badge-blue { background: #e8f0fe; color: var(--fb-blue); }

        /* Friend/Contact row */
        .contact-row {
            display: flex; align-items: center; gap: 12px; padding: 8px;
            border-radius: 8px; cursor: pointer; transition: background 0.2s;
        }
        .contact-row:hover { background: var(--fb-hover); }
        .online-dot-container { position: relative; }
        .online-dot {
            position: absolute; bottom: -2px; right: -2px; width: 10px; height: 10px;
            border-radius: 50%; background: var(--success); border: 2px solid var(--fb-card);
        }

        /* Control Panel Rows (Jobs) */
        .job-row {
            background: var(--fb-input); border-radius: 8px; padding: 12px; margin-bottom: 8px;
            border: 1px solid transparent; transition: 0.2s;
        }
        .job-row.checked { border-color: var(--fb-blue); background: #e8f0fe; }
        .job-row.dragover { border: 2px dashed var(--fb-blue); background: #e8f0fe; }

        .thumb-row-wrap {
            display: flex; align-items: center; justify-content: space-between;
            padding: 8px; background: var(--fb-card); border-radius: 6px; margin-top: 6px;
        }
        .thumb-box {
            width: 48px; height: 48px; background: #000; border-radius: 6px;
            overflow: hidden; border: 1px solid var(--fb-border); position: relative;
        }
        .thumb-box img { width: 100%; height: 100%; object-fit: contain; }
        .pdf-tag {
            position: absolute; bottom: 2px; right: 2px; background: var(--danger);
            color: white; font-size: 8px; padding: 1px 3px; border-radius: 3px; font-weight: bold;
        }

        /* Modals */
        .modal {
            display: none; position: fixed; inset: 0;
            background: rgba(244, 244, 244, 0.85); z-index: 2000;
            align-items: center; justify-content: center; backdrop-filter: blur(4px);
        }
        .modal-box {
            background: var(--fb-card); box-shadow: var(--shadow); border-radius: 8px;
            max-height: 90vh; overflow-y: auto; border: 1px solid var(--fb-border);
        }

        /* Custom Range Slider */
        .cyber-range {
            -webkit-appearance: none; width: 100%; height: 6px;
            background: var(--fb-border); border-radius: 10px; outline: none; margin: 8px 0;
        }
        .cyber-range::-webkit-slider-thumb {
            -webkit-appearance: none; appearance: none; width: 16px; height: 16px;
            border-radius: 50%; background: var(--fb-blue); cursor: pointer; transition: 0.2s;
        }

        /* Label Invoice Style */
        .inv-label-top {
            position: absolute; font-size: 10pt; font-family: 'Outfit', sans-serif;
            font-weight: 700; color: #000; background: rgba(255,255,255,0.95);
            padding: 2px 10px; border-radius: 4px; white-space: nowrap; z-index: 50;
            box-shadow: 0 1px 3px rgba(0,0,0,0.3);
        }

        /* Manual Layouter CSS */
        #modal-manual-layout {
            display: none; position: fixed; inset: 0; background: var(--fb-bg); z-index: 5000;
            grid-template-columns: 320px 1fr;
        }
        .layout-sidebar { background: var(--fb-card); border-right: 1px solid var(--fb-border); padding: 16px; overflow-y: auto; display: flex; flex-direction: column; }
        .layout-main { background: #000; display: flex; flex-direction: column; align-items: center; padding: 32px; overflow-y: auto; }
        .paper-canvas { background: white; position: relative; box-shadow: 0 0 30px rgba(0,0,0,0.5); min-height: 100px; }
        .canvas-item { position: absolute; border: 1px solid transparent; }
        .canvas-item:hover { border: 1px solid var(--fb-blue); }
        .canvas-item .item-del {
            position: absolute; top: -10px; right: -10px; background: var(--danger);
            color: white; width: 20px; height: 20px; border-radius: 50%;
            display: flex; align-items: center; justify-content: center; font-size: 12px; cursor: pointer;
        }

        /* Toast notification */
        .toast {
            position: fixed; bottom: 30px; right: 30px; padding: 12px 24px;
            background: var(--fb-blue); color: #fff; font-weight: bold;
            border-radius: 30px; box-shadow: var(--shadow); z-index: 20000;
            font-size: 0.9rem; animation: fadeIn 0.3s ease;
        }
        .toast.error { background: var(--danger); }
        .toast.info { background: var(--fb-text-dim); }

        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(10px); }
            to { opacity: 1; transform: translateY(0); }
        }

        /* Reload button animation */
        .btn-reload.spin {
            animation: spin 0.6s ease-in-out;
        }
        @keyframes spin {
            0% { transform: rotate(0deg); }
            100% { transform: rotate(360deg); }
        }
    </style>
</head>
<body>
    <!-- AUDIO FILES -->
    <audio id="notif-sound" src="notif.mp3" preload="auto"></audio>
    <audio id="conn-sound" src="conn.mp3" preload="auto"></audio>
    <audio id="done-sound" src="done.mp3" preload="auto"></audio>

    <!-- LOGOUT CONFIRM MODAL -->
    <div id="logout-confirm" class="modal">
        <div class="fb-card-panel" style="width:320px; text-align:center;">
            <h3>Logout dari system?</h3>
            <p style="color:var(--fb-text-dim); font-size:0.85rem; margin-bottom:20px;">Sesi aktif Anda akan segera diakhiri.</p>
            <div style="display:flex; gap:10px;">
                <button class="btn btn-outline" style="flex:1" onclick="closeLogoutConfirm()">BATAL</button>
                <button class="btn btn-danger" style="flex:1" onclick="confirmLogout()">LOGOUT</button>
            </div>
        </div>
    </div>

    <!-- PROMPT CUSTOM -->
    <div id="kts-prompt" class="modal">
        <div class="fb-card-panel" style="width: 360px; text-align: center; border: 1px solid var(--fb-blue);">
            <h3 id="p-title" style="margin-top:0; color:var(--fb-blue);">Input Required</h3>
            <p id="p-desc" style="font-size:0.85rem; color:var(--fb-text-dim); margin-bottom:20px;"></p>
            <input type="text" id="p-val" class="fb-input" autocomplete="off" style="text-align:center; font-weight:bold;">
            <div style="display:flex; gap:10px; margin-top:25px;">
                <button class="btn btn-outline" style="flex:1" onclick="closeKtsPrompt()">CANCEL</button>
                <button class="btn btn-primary" style="flex:1" onclick="confirmKts()">OK</button>
            </div>
        </div>
    </div>

    <!-- LOGIN SCREEN (FACEBOOK BLUE STYLE) -->
    <div id="login-screen">
        <div class="login-header-logo">thinkflow</div>
        <p style="color:var(--fb-text-dim); margin-bottom:30px; font-weight:600; font-size:1.1rem;">Hubungkan, Desain, dan Cetak Tanpa Hambatan.</p>
        <div class="login-box">
            <h2 style="margin-top:0; font-size:1.2rem; color:var(--fb-text);">Masuk ke Antarmuka Peran</h2>
            <div class="role-grid">
                <div class="role-card" data-role="admin"><i>🕶️</i><span>ADMIN</span></div>
                <div class="role-card" data-role="designer"><i>🎨</i><span>DESIGNER</span></div>
                <div class="role-card" data-role="operator"><i>🖨️</i><span>OPERATOR</span></div>
            </div>
            <div style="margin-top:30px; border-top:1px solid var(--fb-border); padding-top:20px; display:flex; gap:10px; justify-content:center;">
                <button id="btn-cloud" class="btn btn-primary">CLOUD CLUSTER</button>
                <button id="btn-local" class="btn btn-outline">LOCAL LAN MODE</button>
            </div>
        </div>
    </div>

    <!-- FB TOP BAR NAVIGATION -->
    <div id="fb-top-bar" style="display:none;">
        <div class="top-left">
            <div class="top-logo">T</div>
            <div class="top-logo-text">thinkflow</div>
            <div class="top-search-container">
                <i class="search-icon">🔍</i>
                <input type="text" id="timeline-search-input" class="fb-input" placeholder="Cari invoice..." onkeyup="searchTimeline()">
            </div>
        </div>
        <div class="top-middle-tabs">
            <div class="nav-tab active" title="Umpan Utama / Feed Timeline">🏠</div>
            <div class="nav-tab role-operator-only" id="btn-open-layouter-top" onclick="openManualLayouter()" title="Layouter Manual 2D">🧩</div>
            <div class="nav-tab" onclick="location.reload()" title="Segarkan System">🔄</div>
            <div class="nav-tab" onclick="toggleHistory()" title="Production Log">📋</div>
        </div>
        <div class="top-right">
            <div class="profile-badge">
                <div class="avatar-circle" id="role-avatar">A</div>
                <span id="active-role-display">ADMIN</span>
            </div>
            <button class="btn btn-outline btn-mini" onclick="doLogout()" style="border-radius:50%; width:36px; height:36px; padding:0;" title="Keluar / Logout">🚪</button>
        </div>
    </div>

    <!-- MAIN APP LAYOUT (GRID 3 COLUMN) -->
    <div id="app-layout">
        <!-- LEFT SIDEBAR: NAVIGATION SHORTCUTS & CONTACTS -->
        <div class="sidebar-left">
            <div class="fb-card-panel" style="padding: 12px;">
                <h4 style="margin:0 0 10px 0; color:var(--fb-text-dim); font-size:0.8rem; text-transform:uppercase;">Identitas Node</h4>
                <div id="my-id-container" style="font-size:0.85rem; padding:8px; background:var(--fb-input); border-radius:8px;">
                    <strong>ID LOKAL:</strong> 
                    <span id="my-id-display" style="color:var(--fb-blue); font-weight:bold; cursor:pointer;" title="Klik untuk mengedit ID">...</span>
                    <input type="text" id="my-id-editor" style="display:none; width:100%; font-size:0.8rem;" class="fb-input">
                </div>
                <div id="status-widget" style="margin-top:8px; font-weight:700; font-size:0.8rem; display:flex; align-items:center;">
                    <span class="online-dot" style="position:static; display:inline-block; margin-right:6px;"></span>
                    <span id="status-text">OFFLINE</span>
                </div>
            </div>

            <!-- Panel Sambungan Peer Baru -->
            <div class="fb-card-panel" style="padding: 12px;">
                <h4 style="margin:0 0 10px 0; color:var(--fb-text-dim); font-size:0.8rem; text-transform:uppercase;">Sambungan Baru</h4>
                <input type="text" id="target-id" class="fb-input" placeholder="Masukkan ID Partner..." style="margin-bottom:8px;">
                <button class="btn btn-primary" style="width:100%;" onclick="connectMulti()">Hubungkan Node</button>
            </div>

            <!-- Kontak Aktif (Online Peers) -->
            <div class="fb-card-panel" style="flex:1; padding:12px;">
                <h4 style="margin:0 0 10px 0; color:var(--fb-text-dim); font-size:0.8rem; text-transform:uppercase;">Kontak Node Aktif</h4>
                <div id="active-conns" style="display:flex; flex-direction:column; gap:4px;"></div>
            </div>
        </div>

        <!-- MIDDLE FEED: TIMELINE & COMPOSER -->
        <div class="feed-container">
            <!-- Batch Printing Control (Hanya Operator) -->
            <div id="batch-bar" class="fb-card-panel role-operator-only" style="display:none; justify-content:space-between; align-items:center; background:#e7f3e8; border:1px solid var(--success);">
                <span id="batch-count" style="font-weight:700; color:var(--success); font-size:0.85rem;">0 ITEM DIPILIH</span>
                <button class="btn btn-success btn-mini" onclick="openBatchPrint()">📄 BATCH PDF</button>
            </div>

            <!-- COMPOSER BOX: Hanya Admin & Designer yang dapat mengirim data baru ke node lain -->
            <div class="composer-box role-admin-only role-designer-only">
                <div class="composer-header">
                    <div class="avatar-circle">M</div>
                    <button class="composer-trigger" onclick="addNewJob()">Buat baris atau paket pengiriman baru...</button>
                </div>
                <div class="composer-options">
                    <div class="comp-opt" onclick="triggerFileSelect(activeJobIdx || 0)">📁 Unggah Gambar/PDF</div>
                    <div class="comp-opt" onclick="toggleSelectAllRows()">✅ Pilih Semua Baris</div>
                </div>
            </div>

            <!-- FEED SECTIONS (TIMELINE) -->
            <div class="fb-card-panel" style="padding:12px 16px; display:flex; justify-content:space-between; align-items:center;">
                <span style="font-weight:700; color:var(--fb-text-dim); font-size:0.85rem;">POSTINGAN TIMELINE</span>
                <div id="filter-bar" style="display:flex; gap:6px;"></div>
                <button class="btn btn-danger btn-mini" onclick="clearTimeline()">🗑️ CLEAR</button>
            </div>

            <!-- Alur Stream / Umpan utama -->
            <div id="stream-area"></div>
        </div>

        <!-- RIGHT SIDEBAR: WORKSPACE DETAIL SPESIFIK TIAP ROLE -->
        <div class="sidebar-right">
            <!-- WORKSPACE UNTUK ADMIN: Panel Input Parameter Desain/Job -->
            <div class="role-admin-only">
                <div class="fb-card-panel">
                    <h3 style="margin-top:0; font-size:1rem; color:var(--fb-blue);">Control Room: Admin</h3>
                    <p style="font-size:0.8rem; color:var(--fb-text-dim);">Gunakan form di bawah untuk merancang job desain awal.</p>
                    <div id="job-list"></div>
                    <button class="btn btn-outline" style="border-style:dashed; width:100%; margin-top:8px;" onclick="addNewJob()">➕ TAMBAH DATA BARIS</button>
                    <button id="btn-action-main" class="btn btn-primary" style="width:100%; margin-top:16px; height:45px;" onclick="mainAction()">⚡ KIRIM KE DESIGNER</button>
                </div>
            </div>

            <!-- WORKSPACE UNTUK DESIGNER: Galeri Asset Marketplace & Form Draft -->
            <div class="role-designer-only">
                <div class="fb-card-panel">
                    <h3 style="margin-top:0; font-size:1rem; color:var(--fb-blue);">Galeri Inspirasi & Aset</h3>
                    <p style="font-size:0.85rem; color:var(--fb-text-dim); margin-bottom:12px;">Saran Halaman & Aset (Klik untuk masukkan langsung ke formulir aktif):</p>
                    <div id="gallery-container" style="display:grid; grid-template-columns:repeat(3, 1fr); gap:8px; max-height:260px; overflow-y:auto; padding-bottom:10px;"></div>
                    <button class="btn btn-outline btn-mini" style="width:100%; margin-top:8px;" onclick="refreshGallery()">⟳ Segarkan Database Aset</button>
                </div>
                <div class="fb-card-panel">
                    <h4 style="margin-top:0;">Form Penyebaran Ke Operator</h4>
                    <div id="designer-job-list-placeholder"></div>
                    <button id="btn-designer-action" class="btn btn-primary" style="width:100%; margin-top:10px;" onclick="mainAction()">🚀 SETORKAN KE OPERATOR</button>
                </div>
            </div>

            <!-- WORKSPACE UNTUK OPERATOR: Parameter Cetak Cepat & Tombol Modul Layouter -->
            <div class="role-operator-only">
                <div class="fb-card-panel" style="border-left: 4px solid var(--success);">
                    <h3 style="margin-top:0; font-size:1rem; color:var(--success);">Operator Engine</h3>
                    <p style="font-size:0.8rem; color:var(--fb-text-dim);">Kelola, tata letak ulang inspirasi cetakan manual, atau lakukan aksi cetakan langsung pada antrean.</p>
                    <button class="btn btn-success" style="width:100%; height:45px; margin-bottom:12px;" onclick="openManualLayouter()">🧩 BUKA MANUAL LAYOUTER 2D</button>
                    <div style="font-size:0.75rem; color:var(--fb-text-dim); line-height:1.4;">
                        *Gunakan tombol <strong>BATCH</strong> di bagian atas timeline untuk mengumpulkan berkas cetak bertipe PDF ke dalam tata letak global secara cepat.
                    </div>
                </div>
                <div class="fb-card-panel">
                    <h4 style="margin-top:0;">Daftar Mandiri (Lokal)</h4>
                    <div id="operator-job-list-placeholder"></div>
                    <button class="btn btn-outline" style="width:100%; border-style:dashed;" onclick="addNewJob()">➕ TAMBAH DATA BARIS</button>
                    <button class="btn btn-primary" style="width:100%; margin-top:10px;" onclick="mainAction()">🖨️ PROSES CETAK MANUAL</button>
                </div>
            </div>
        </div>
    </div>

    <!-- INPUT FILE TERSEMBUNYI -->
    <input type="file" id="job-file-in" multiple style="display:none;" onchange="handleFileSelect(this)">

    <!-- MODAL: MANUAL LAYOUTER (OPERATOR) -->
    <div id="modal-manual-layout">
        <div class="layout-sidebar">
            <div style="display:flex; justify-content:space-between; align-items:center; margin-bottom:16px; gap:8px;">
                <button class="btn btn-outline btn-mini" onclick="closeManualLayouter()">⬅️ KEMBALI</button>
                <span style="font-weight:bold; color:var(--fb-blue); white-space:nowrap;">🧩 LAYOUTER 2D</span>
                <div style="display:flex; gap:4px;">
                    <!-- Tombol Reload (baru) -->
                    <button class="btn btn-outline btn-mini" id="btn-reload-layouter" onclick="reloadLayouter()" title="Muat Ulang Layouter" style="border-radius: 50%; width: 32px; height: 32px; padding: 0; display: inline-flex; align-items: center; justify-content: center; font-size: 1.1rem;">🔄</button>
                    <!-- Tombol Cetak -->
                    <button class="btn btn-success btn-mini" onclick="openLayoutPrintModal()" title="Konfigurasi Cetak Layouter" style="border-radius: 50%; width: 32px; height: 32px; padding: 0; display: inline-flex; align-items: center; justify-content: center; font-size: 1.1rem;">🖨️</button>
                </div>
            </div>
            <div class="fb-card-panel" style="padding:10px; margin-bottom:12px; background:var(--fb-input); border:none;">
                <label style="font-size:0.75rem; font-weight:bold; display:block; margin-bottom:4px;">UNGGAH BERKAS SUMBER</label>
                <input type="file" id="manual-upload-in" multiple accept="image/*" onchange="handleManualUpload(this)" class="fb-input" style="font-size:0.75rem;">
            </div>
            <div style="display:grid; grid-template-columns:1fr 1fr; gap:6px; margin-bottom:12px;">
                <div>
                    <label style="font-size:0.7rem; font-weight:600;">LEBAR (cm)</label>
                    <input type="number" id="m-w" value="5" step="0.1" class="fb-input" oninput="recalculateLayout(); renderCanvasItems();">
                </div>
                <div>
                    <label style="font-size:0.7rem; font-weight:600;">TINGGI (cm)</label>
                    <input type="number" id="m-h" value="5" step="0.1" class="fb-input" oninput="recalculateLayout(); renderCanvasItems();">
                </div>
            </div>
            
            <div style="flex:1; overflow-y:auto; border-top:1px solid var(--fb-border); padding-top:12px;">
                <div style="display:flex; justify-content:space-between; align-items:center; margin-bottom:8px; border-bottom:1px solid var(--fb-border); padding-bottom:6px;">
                    <h4 style="margin:0; color:var(--fb-blue);">Galeri Sumber Aset</h4>
                    <button class="btn btn-outline btn-mini" onclick="loadImagesFromManifest(); showToast('🔄 Aset berhasil dimuat ulang!', 'success');" title="Memuat Ulang Aset" style="padding: 2px 6px;">🔄 Muat Ulang</button>
                </div>
                <div id="manual-source-list" style="display:grid; grid-template-columns:1fr 1fr; gap:8px;"></div>
            </div>
        </div>
        <div class="layout-main">
            <div style="margin-bottom:20px; display:flex; gap:16px; align-items:center; background:rgba(255,255,255,0.1); padding:8px 24px; border-radius:30px;">
                <select id="m-paper" class="fb-input" style="width:160px;" onchange="updatePaperCanvas()">
                    <option value="32,48">A3+ (32x48 cm)</option>
                    <option value="32,45">SRA3 (32x45 cm)</option>
                    <option value="21,29.7">A4 (21x29.7 cm)</option>
                </select>
                <button class="btn btn-danger btn-mini" onclick="clearManualCanvas()">🗑️ BERSIHKAN</button>
            </div>
            <div id="paper-canvas" class="paper-canvas"></div>
        </div>
    </div>

    <!-- MODAL: DETAILED PENGATURAN CETAK LAYOUTER (NEW SEPARATED IMG SETTING - FIXED Z-INDEX) -->
    <div id="modal-layout-print" class="modal" style="z-index: 6000;">
        <div class="modal-box" style="width:640px; padding:24px;">
            <h2 style="margin-top:0; border-bottom:1px solid var(--fb-border); padding-bottom:12px; color:var(--fb-blue);">🧩 PENGATURAN CETAK LAYOUTER 2D</h2>
            <div style="display:grid; grid-template-columns:1fr 1fr; gap:16px; margin-bottom:20px;">
                <div>
                    <label style="font-weight:bold; font-size:0.75rem; color:var(--fb-text-dim);">NOMOR INVOICE LAYOUT</label>
                    <input type="text" id="l-inv" class="fb-input" style="font-weight:bold; color:var(--danger);" value="LAY-001">
                </div>
                <div>
                    <label style="font-weight:bold; font-size:0.75rem; color:var(--fb-text-dim);">JENIS MATERIAL</label>
                    <select id="l-mat" class="fb-input">
                        <option>Chromo</option>
                        <option>Vinyl Glossy</option>
                        <option>Vinyl Matte</option>
                        <option>Transparan</option>
                        <option>Art Carton</option>
                        <option>HVS</option>
                    </select>
                </div>
            </div>

            <!-- MARGIN KERTAS -->
            <div class="fb-card-panel" style="padding:10px; margin-bottom:12px;">
                <label style="font-weight:bold; font-size:0.75rem; display:block; margin-bottom:6px;">MARGIN HALAMAN (cm)</label>
                <div style="display:grid; grid-template-columns:repeat(4, 1fr); gap:6px;">
                    <div><label style="font-size:0.65rem;">ATAS</label><input type="number" id="l-margin-top" value="0.5" step="0.1" class="fb-input"></div>
                    <div><label style="font-size:0.65rem;">BAWAH</label><input type="number" id="l-margin-bottom" value="0.5" step="0.1" class="fb-input"></div>
                    <div><label style="font-size:0.65rem;">KIRI</label><input type="number" id="l-margin-left" value="0.5" step="0.1" class="fb-input"></div>
                    <div><label style="font-size:0.65rem;">KANAN</label><input type="number" id="l-margin-right" value="0.5" step="0.1" class="fb-input"></div>
                </div>
            </div>

            <!-- CROP MARKS / TANDA POTONG -->
            <div class="fb-card-panel" style="padding:10px; margin-bottom:12px;">
                <div style="display:flex; align-items:center; gap:6px; margin-bottom:8px;">
                    <input type="checkbox" id="l-use-kres" checked>
                    <label for="l-use-kres" style="font-weight:600; font-size:0.75rem;">GUNAKAN TANDA POTONG</label>
                </div>
                <div style="display:grid; grid-template-columns:1fr 1fr 1fr; gap:6px;">
                    <div><label style="font-size:0.6rem; font-weight:600;">TEBAL(mm)</label><input type="number" id="l-kres-tebal" value="0.3" step="0.1" class="fb-input"></div>
                    <div><label style="font-size:0.6rem; font-weight:600;">PANJANG(mm)</label><input type="number" id="l-kres-panjang" value="5" step="1" class="fb-input"></div>
                    <div><label style="font-size:0.6rem; font-weight:600;">OFFSET(mm)</label><input type="number" id="l-kres-offset" value="0" step="0.5" class="fb-input"></div>
                </div>
            </div>

            <div style="display:grid; grid-template-columns:1fr 1fr; gap:12px; margin-bottom:12px;">
                <div>
                    <label style="font-size:0.7rem; font-weight:600;">JARAK / GAP ANTAR GAMBAR (cm)</label>
                    <input type="number" id="l-gap" value="0" step="0.1" class="fb-input" oninput="recalculateLayout(); renderCanvasItems();">
                </div>
                <div>
                    <label style="font-size:0.7rem; font-weight:600;">QTY LEMBAR PENERBITAN</label>
                    <input type="number" id="l-qty" value="1" min="1" class="fb-input" style="font-weight:bold; color:var(--success);">
                </div>
            </div>

            <div style="display:grid; grid-template-columns:1fr 2fr; gap:12px; margin-top:20px;">
                <button class="btn btn-outline" onclick="closeLayoutPrintModal()">BATAL</button>
                <button id="btn-do-layout-print" class="btn btn-primary" onclick="executeLayoutPrint()">MULAI CETAK LAYOUT</button>
            </div>
        </div>
    </div>

    <!-- MODAL: PRODUCTION HISTORY LOG & PRINT SETUP -->
    <div id="modal-print" class="modal">
        <div class="modal-box" style="width:640px; padding:24px;">
            <h2 style="margin-top:0; border-bottom:1px solid var(--fb-border); padding-bottom:12px; color:var(--fb-blue);">🖨️ PENGATURAN CETAK PRODUKSI</h2>
            <div style="display:grid; grid-template-columns:140px 1fr; gap:16px; margin-bottom:20px;">
                <div style="text-align:center;">
                    <div style="width:130px; height:130px; border-radius:6px; background:#000; overflow:hidden; border:1px solid var(--fb-border); display:flex; align-items:center; justify-content:center; position:relative;">
                        <img id="p-img" style="max-width:100%; max-height:100%; object-fit:contain; transition:transform 0.2s;">
                        <div id="p-pdf-badge" class="pdf-tag" style="display:none;">PDF</div>
                    </div>
                    <button class="btn btn-outline btn-mini" onclick="rotatePreviewImage()" style="margin-top:6px;">🔄 ROTASI</button>
                </div>
                <div style="display:flex; flex-direction:column; gap:10px;">
                    <div>
                        <label style="font-weight:bold; font-size:0.75rem; color:var(--fb-text-dim);">NOMOR INVOICE</label>
                        <input type="text" id="p-inv-edit" class="fb-input" style="font-weight:bold; color:var(--danger);">
                    </div>
                    <div>
                        <label style="font-weight:bold; font-size:0.75rem; color:var(--fb-text-dim);">JENIS MATERIAL</label>
                        <select id="p-mat" class="fb-input">
                            <option>Chromo</option>
                            <option>Vinyl Glossy</option>
                            <option>Vinyl Matte</option>
                            <option>Transparan</option>
                            <option>Art Carton</option>
                            <option>HVS</option>
                        </select>
                    </div>
                </div>
            </div>
            <div style="display:flex; gap:10px; margin-bottom:16px;">
                <button id="mode-full-btn" class="btn btn-outline" style="flex:1;" onclick="switchPrintMode('full')">📄 SATU HALAMAN PENUH</button>
                <button id="mode-grid-btn" class="btn btn-outline" style="flex:1;" onclick="switchPrintMode('grid')">🔲 GRID TILE (POTONGAN)</button>
            </div>
            <div class="fb-card-panel" style="background:var(--fb-input); border:none;">
                <label style="font-weight:600; font-size:0.75rem;">UKURAN KERTAS CETAK</label>
                <select id="p-pdf-paper" class="fb-input" onchange="toggleCustomPaper(this.value)" style="margin-bottom:10px;">
                    <option value="32,48">A3+ (32x48 cm)</option>
                    <option value="32,45">SRA3 (32x45 cm)</option>
                    <option value="29.7,42">A3</option>
                    <option value="21,29.7">A4</option>
                    <option value="custom">⚙️ KUSTOMISASI</option>
                </select>
                <div id="custom-paper-box" style="display:none; gap:10px;">
                    <input type="number" id="p-custom-w" class="fb-input" placeholder="Lebar (cm)" oninput="calcGrid()">
                    <input type="number" id="p-custom-h" class="fb-input" placeholder="Tinggi (cm)" oninput="calcGrid()">
                </div>
                <div id="grid-controls" style="display:none; border-top:1px dashed var(--fb-border); padding-top:12px; margin-top:12px;">
                    <div style="display:grid; grid-template-columns:1fr 1fr 1fr auto; gap:8px; align-items:flex-end;">
                        <div><label style="font-size:0.7rem;">LEBAR (cm)</label><input type="number" id="p-grid-w" value="5" step="0.1" class="fb-input" oninput="calcGrid()"></div>
                        <div><label style="font-size:0.7rem;">TINGGI (cm)</label><input type="number" id="p-grid-h" value="5" step="0.1" class="fb-input" oninput="calcGrid()"></div>
                        <div><label style="font-size:0.7rem;">GAP (cm)</label><input type="number" id="p-grid-gap" value="0" step="0.1" class="fb-input" oninput="calcGrid()"></div>
                        <button class="btn btn-outline" onclick="physicalRotate()">🔄</button>
                    </div>
                    <div style="display:grid; grid-template-columns:1fr 1fr; gap:10px; margin-top:10px; border-top:1px dashed var(--fb-border); padding-top:10px;">
                        <div><label style="font-size:0.7rem;">TEBAL CROP (mm)</label><input type="number" id="p-grid-kres-thick" value="0.2" step="0.1" class="fb-input" oninput="calcGrid()"></div>
                        <div><label style="font-size:0.7rem;">PANJANG CROP (mm)</label><input type="number" id="p-grid-kres-len" value="5" step="1" class="fb-input" oninput="calcGrid()"></div>
                    </div>
                    <div style="display:grid; grid-template-columns:1fr 1fr; gap:10px; margin-top:10px;">
                        <div><label style="font-size:0.7rem;">OFFSET JARAK (mm)</label><input type="number" id="p-grid-kres-offset" value="0" step="0.5" class="fb-input" oninput="calcGrid()"></div>
                        <div style="display:flex; align-items:center; gap:6px; margin-top:15px;">
                            <input type="checkbox" id="p-grid-show-kres" checked onchange="calcGrid()">
                            <label for="p-grid-show-kres" style="font-size:0.7rem; font-weight:bold; cursor:pointer;">TAMPILKAN TANDA POTONG</label>
                        </div>
                    </div>
                    <div id="grid-res-box" style="text-align:center; color:var(--fb-blue); font-weight:bold; font-size:0.85rem; margin-top:12px;">HASIL: -</div>
                </div>

                <!-- INDIVIDUAL PHOTO QUANTITY LIST (NEW WITH AUTO FILL BAGI RATA FEATURE) -->
                <div id="grid-individual-qtys" style="display:none; margin-top:12px; border-top:1px dashed var(--fb-border); padding-top:12px;">
                    <div style="display:flex; justify-content:space-between; align-items:center; margin-bottom:8px;">
                        <label style="font-weight:bold; font-size:0.75rem; color:var(--fb-blue); margin:0;">⚙️ PENGATURAN QUANTITY PER FOTO</label>
                        <button class="btn btn-success btn-mini" onclick="autoDistributeQtys()" style="font-size:0.65rem; padding:2px 8px;" title="Bagi rata seluruh foto ke dalam kapasitas 1 lembar kertas">⚡ BAGI RATA 1 LEMBAR</button>
                    </div>
                    <div id="grid-individual-list" style="display:flex; flex-direction:column; gap:8px; max-height:160px; overflow-y:auto; padding-right:4px;"></div>
                </div>

                <div style="margin-top:12px; display:flex; gap:16px; align-items:center;">
                    <label style="font-weight:bold; font-size:0.75rem;">QTY LEMBAR PENERBITAN</label>
                    <input type="number" id="p-pdf-target" value="1" min="1" class="fb-input" style="width:100px; text-align:center; color:var(--success); font-weight:bold;" oninput="calcGrid()">
                </div>
            </div>

            <!-- MARGIN KERTAS -->
            <div class="fb-card-panel" style="padding:10px; margin-bottom:12px;">
                <label style="font-weight:bold; font-size:0.75rem; display:block; margin-bottom:6px;">MARGIN HALAMAN (cm)</label>
                <div style="display:grid; grid-template-columns:repeat(4, 1fr); gap:6px;">
                    <div><label style="font-size:0.65rem;">ATAS</label><input type="number" id="p-margin-top" value="0.5" step="0.1" class="fb-input" oninput="updatePrintPreview()"></div>
                    <div><label style="font-size:0.65rem;">BAWAH</label><input type="number" id="p-margin-bottom" value="0.5" step="0.1" class="fb-input" oninput="updatePrintPreview()"></div>
                    <div><label style="font-size:0.65rem;">KIRI</label><input type="number" id="p-margin-left" value="0.5" step="0.1" class="fb-input" oninput="updatePrintPreview()"></div>
                    <div><label style="font-size:0.65rem;">KANAN</label><input type="number" id="p-margin-right" value="0.5" step="0.1" class="fb-input" oninput="updatePrintPreview()"></div>
                </div>
            </div>

            <!-- LABEL KUSTOMISASI -->
            <div class="fb-card-panel" style="padding:10px;">
                <label style="font-weight:bold; font-size:0.75rem; display:block; margin-bottom:6px;">🏷️ POSISI & AKTIVITAS LABEL</label>
                <div style="display:grid; grid-template-columns:1fr 1fr; gap:12px;">
                    <div>
                        <div style="display:flex; justify-content:space-between; font-size:0.7rem;"><span>↔️ Horizontal</span><span id="label-x-val">0.5 cm</span></div>
                        <input type="range" id="p-label-x" min="0" max="100" value="5" class="cyber-range" oninput="updatePrintPreview()">
                    </div>
                    <div>
                        <div style="display:flex; justify-content:space-between; font-size:0.7rem;"><span>↕️ Vertikal</span><span id="label-y-val">0.5 cm</span></div>
                        <input type="range" id="p-label-y" min="0" max="100" value="5" class="cyber-range" oninput="updatePrintPreview()">
                    </div>
                </div>
                <div style="display:flex; gap:12px; margin-top:8px;">
                    <div style="display:flex; align-items:center; gap:4px;">
                        <input type="checkbox" id="p-show-inv-label" checked onchange="updatePrintPreview()">
                        <label for="p-show-inv-label" style="font-size:0.70rem; font-weight:600;">CETAK NO. INV</label>
                    </div>
                    <div style="display:flex; align-items:center; gap:4px;">
                        <input type="checkbox" id="p-show-mat-label" checked onchange="updatePrintPreview()">
                        <label for="p-show-mat-label" style="font-size:0.70rem; font-weight:600;">CETAK MATERIAL</label>
                    </div>
                </div>
                <!-- Preview area mini -->
                <div style="margin-top:10px; height:50px; background:var(--fb-input); border-radius:6px; position:relative; overflow:hidden;">
                    <div id="label-preview-dot" style="position:absolute; top:10px; left:10px; background:var(--fb-blue); color:white; font-size:0.65rem; padding:2px 8px; border-radius:4px; font-weight:bold; white-space:nowrap;">
                        INV-001 - Chromo
                    </div>
                </div>
            </div>

            <div style="display:grid; grid-template-columns:1fr 2fr; gap:12px; margin-top:20px;">
                <button class="btn btn-outline" onclick="closeModal()">BATAL</button>
                <button id="btn-do-print" class="btn btn-primary" onclick="executePrint()">MULAI CETAK</button>
            </div>
        </div>
    </div>

    <!-- MODAL: PRODUCTION HISTORY LOG -->
    <div id="modal-hist" class="modal">
        <div class="modal-box" style="width:90%; max-width:1100px; padding:24px;">
            <div style="display:flex; justify-content:space-between; align-items:center; border-bottom:1px solid var(--fb-border); padding-bottom:12px; margin-bottom:16px;">
                <h2 style="margin:0;">📁 LAPORAN LOG PRODUKSI - <span id="hist-role-title" style="color:var(--fb-blue);"></span></h2>
                <div style="display:flex; gap:8px;">
                    <button class="btn btn-success btn-mini" onclick="exportLogToPDF()">📄 EKSPOR KE PDF</button>
                    <button class="btn btn-danger btn-mini" onclick="clearAllHistory()">🗑️ BERSIHKAN SEMUA LOG</button>
                </div>
            </div>
            <div style="display:grid; grid-template-columns:2fr 1fr; gap:10px; margin-bottom:16px;">
                <input type="text" id="hist-search-input" class="fb-input" placeholder="🔍 Cari Invoice, Partner, atau Keterangan..." onkeyup="filterHistoryTable()">
                <input type="date" id="hist-search-date" class="fb-input" style="color-scheme: light;" onchange="filterHistoryTable()">
            </div>
            <div style="display:flex; gap:4px; margin-bottom:12px; background:var(--fb-input); padding:4px; border-radius:6px;">
                <button class="btn btn-outline btn-mini active" id="tab-1" onclick="switchHistTab(1)" style="flex:1;">INBOX / DATA MASUK</button>
                <button class="btn btn-outline btn-mini" id="tab-2" onclick="switchHistTab(2)" style="flex:1;">OUTBOX / HASIL PRODUKSI</button>
                <button class="btn btn-outline btn-mini" id="tab-3" onclick="switchHistTab(3)" style="flex:1; display: none;">📊 HASIL LAYOUTER 2D</button>
            </div>
            <div style="max-height:400px; overflow-y:auto; border:1px solid var(--fb-border); border-radius:6px;">
                <table id="hist-table-real" style="width:100%; border-collapse:collapse; background:white; font-size:0.8rem; text-align:left;">
                    <thead>
                        <tr style="background:var(--fb-input); border-bottom:2px solid var(--fb-border);">
                            <th style="padding:10px;">WAKTU</th>
                            <th style="padding:10px;">BERKAS</th>
                            <th style="padding:10px;">STATUS ALUR</th>
                            <th style="padding:10px;">MITRA NODE</th>
                            <th style="padding:10px;">INVOICE</th>
                            <th style="padding:10px;">KETERANGAN</th>
                            <th style="padding:10px;">QTY</th>
                            <th style="padding:10px;">AKSI</th>
                        </tr>
                    </thead>
                    <tbody id="hist-body"></tbody>
                </table>
            </div>
            <button class="btn btn-outline" style="width:100%; margin-top:20px;" onclick="toggleHistory()">TUTUP</button>
        </div>
    </div>

    <!-- TEMPLATE CARDS -->
    <template id="msg-card-template">
        <div class="msg-card">
            <div class="msg-header">
                <div class="poster-info">
                    <div class="avatar-circle" style="background:#555;">U</div>
                    <div class="poster-meta">
                        <span class="poster-name">Unknown Role</span>
                        <span class="poster-sub">Baru Saja · 🌐</span>
                    </div>
                </div>
                <span class="msg-close-trigger" style="cursor:pointer; color:var(--fb-text-dim); font-weight:bold; font-size:1.1rem; padding:4px 8px;">✕</span>
            </div>
            <div class="msg-body">
                <div class="msg-body-caption">Caption area text</div>
                <div class="asset-attachment-container"></div>
            </div>
            <div class="msg-footer"></div>
        </div>
    </template>

    <iframe id="p-frame" style="display:none;"></iframe>

    <script>
        // ========================================================
        // THINK FLOW - WEB EDITION (OVERHAULED JAVASCRIPT CORE)
        // ========================================================

        const ROLES_KEYS = { admin: "calik", designer: "melengkung", operator: "nangtung" };

        let myId = localStorage.getItem('kts_id');
        if (!myId) {
            myId = 'KTS-' + Math.floor(Math.random() * 9000 + 1000);
            localStorage.setItem('kts_id', myId);
        }

        let role = null;
        let peer = null;
        let db = null;
        let activeConns = [];
        let selectedPeersMap = {};
        let currentTab = 1;
        let timelineFilter = 'outbox';
        let tempJobs = [];
        let activeJobIdx = null;
        let selectedInboxes = [];
        let currentPrintMode = 'full';
        let activeJob = null;
        let currentPromptTask = null;
        let postLogoutMode = false;
        let currentRotation = 0;

        let manualSources = [];
        let galleryAssets = [];
        let canvasItems = [];
        let currentX = 0, currentY = 0, maxRowH = 0;

        let streamCache = [];
        let timelinePage = 0;
        const TIMELINE_PAGE_SIZE = 18;
        let timelineFilteredData = [];
        let isLoadingMore = false;

        pdfjsLib.GlobalWorkerOptions.workerSrc = './libs/pdf.worker.min.js';

        // ---------- INDEXED DB ----------
        const DB_NAME = 'ThinkFlowWebDB_FB';
        const DB_VERSION = 1;
        let openRequest = indexedDB.open(DB_NAME, DB_VERSION);
        openRequest.onupgradeneeded = e => {
            let db = e.target.result;
            if (!db.objectStoreNames.contains('stream')) db.createObjectStore('stream', { keyPath: 'id' });
            if (!db.objectStoreNames.contains('history')) db.createObjectStore('history', { keyPath: 'id', autoIncrement: true });
        };
        openRequest.onsuccess = e => {
            db = e.target.result;
            loadStreamCache();
            checkAutoLogin();
        };
        openRequest.onerror = e => console.error('IndexedDB error:', e);

        // ---------- TOAST ----------
        function showToast(msg, type = 'success') {
            const toast = document.createElement('div');
            toast.className = 'toast ' + (type === 'error' ? 'error' : (type === 'info' ? 'info' : ''));
            toast.innerText = msg;
            document.body.appendChild(toast);
            setTimeout(() => toast.remove(), 3000);
        }

        // ---------- AUDIO ----------
        function playSound(id) {
            let audio = document.getElementById(id);
            if (audio) {
                audio.pause();
                audio.currentTime = 0;
                audio.play().catch(() => {});
            }
        }

        // ---------- PROMPT ----------
        function openKtsPrompt(title, desc, type, callback) {
            document.getElementById('p-title').innerText = title;
            document.getElementById('p-desc').innerText = desc;
            let inp = document.getElementById('p-val');
            inp.type = type; inp.value = '';
            document.getElementById('kts-prompt').style.display = 'flex';
            currentPromptTask = callback;
            setTimeout(() => { inp.focus(); inp.select(); }, 200);
        }
        function closeKtsPrompt() {
            document.getElementById('kts-prompt').style.display = 'none';
            currentPromptTask = null;
        }
        function confirmKts() {
            let v = document.getElementById('p-val').value.trim();
            if (v && currentPromptTask) currentPromptTask(v);
            closeKtsPrompt();
        }

        // ---------- LOGOUT ----------
        function doLogout() { document.getElementById('logout-confirm').style.display = 'flex'; }
        function closeLogoutConfirm() { document.getElementById('logout-confirm').style.display = 'none'; }
        function confirmLogout() {
            closeLogoutConfirm();
            if (peer) peer.destroy();
            localStorage.removeItem('kts_active_role');
            role = null;
            tempJobs = [];
            activeConns = [];
            selectedInboxes = [];
            manualSources = [];
            galleryAssets = [];
            canvasItems = [];
            streamCache = [];
            timelineFilteredData = [];
            
            document.body.className = '';
            document.getElementById('fb-top-bar').style.display = 'none';
            document.getElementById('app-layout').style.display = 'none';
            document.getElementById('login-screen').style.display = 'flex';
            postLogoutMode = true;
            reinitializeLoginListeners();
        }

        // ---------- LOGIN ----------
        function reinitializeLoginListeners() {
            let grid = document.querySelector('.role-grid');
            let newGrid = grid.cloneNode(false);
            let roles = ['ADMIN','DESIGNER','OPERATOR'], icons = ['🕶️','🎨','🖨️'];
            roles.forEach((r,i)=>{
                let card = document.createElement('div');
                card.className = 'role-card';
                card.tabIndex = 0;
                card.innerHTML = `<i>${icons[i]}</i><span>${r}</span>`;
                card.onclick = function(e) {
                    e.preventDefault();
                    enterRole(this.querySelector('span').textContent.toLowerCase());
                };
                card.onkeypress = function(e) {
                    if (e.key==='Enter'||e.key===' ') { e.preventDefault(); this.click(); }
                };
                newGrid.appendChild(card);
            });
            grid.parentNode.replaceChild(newGrid, grid);
            document.getElementById('btn-cloud').onclick = ()=> setMode('cloud');
            document.getElementById('btn-local').onclick = ()=> setMode('local');
        }

        function enterRole(r) {
            openKtsPrompt("Login " + r.toUpperCase(), "Masukkan Sandi Otoritas Peran:", "password", pass => {
                if (pass === ROLES_KEYS[r]) {
                    localStorage.setItem('kts_active_role', r);
                    loadInterface(r);
                } else {
                    alert("❌ SANDI SALAH!");
                    setTimeout(()=>enterRole(r),300);
                }
            });
        }

        // ---------- PROGRAM INITIALIZATION ----------
        function checkAutoLogin() {
            let saved = localStorage.getItem('kts_active_role');
            if (saved) loadInterface(saved);
        }

        function loadInterface(r) {
            role = r;
            postLogoutMode = false;
            
            document.body.className = `role-${role}`;
            document.getElementById('login-screen').style.display = 'none';
            document.getElementById('fb-top-bar').style.display = 'flex';
            document.getElementById('app-layout').style.display = 'grid';
            
            document.getElementById('active-role-display').innerText = role.toUpperCase();
            document.getElementById('role-avatar').innerText = role.substring(0,1).toUpperCase();
            document.getElementById('my-id-display').innerText = myId;

            // Pindahkan Job list container ke penempatan spesifik peran
            const jobList = document.getElementById('job-list');
            if (role === 'admin') {
                document.getElementById('job-list').style.display = 'block';
            } else if (role === 'designer') {
                document.getElementById('designer-job-list-placeholder').appendChild(jobList);
            } else if (role === 'operator') {
                document.getElementById('operator-job-list-placeholder').appendChild(jobList);
            }

            if (role === 'operator') {
                document.getElementById('batch-bar').style.display = 'flex';
                document.getElementById('tab-2').innerText = '📊 DATA HASIL PENCETAKAN';
            } else {
                document.getElementById('tab-2').innerText = 'OUTBOX / RIWAYAT';
            }

            initFilterBar();

            if (role === 'admin') timelineFilter = 'outbox';
            else if (role === 'designer') timelineFilter = 'inbox_admin';
            else if (role === 'operator') timelineFilter = 'inbox_designer';

            activateFilterButton();
            initPeer();
            addNewJob();
            makeMyIdEditable();

            if (role === 'operator' || role === 'designer') {
                loadImagesFromManifest();
            }

            setTimeout(() => renderStream(true), 500);
        }

        // ---------- MY-ID EDITABLE ----------
        function makeMyIdEditable() {
            const displaySpan = document.getElementById('my-id-display');
            const editorInput = document.getElementById('my-id-editor');

            displaySpan.onclick = function(e) {
                e.stopPropagation();
                displaySpan.style.display = 'none';
                editorInput.value = myId;
                editorInput.style.display = 'inline-block';
                editorInput.focus();
                editorInput.select();
            };

            function processIdChange() {
                const newId = editorInput.value.trim();
                if (newId === '' || newId === myId) {
                    editorInput.style.display = 'none';
                    displaySpan.style.display = 'inline';
                    return;
                }
                openKtsPrompt("🔐 Verifikasi Otoritas", "Masukkan sandi perubahan (4869):", "password", (code) => {
                    if (code === "4869") {
                        localStorage.setItem('kts_id', newId);
                        showToast(`✅ ID berhasil diubah ke: ${newId}`, 'success');
                        location.reload();
                    } else {
                        alert("❌ Kode akses salah!");
                        editorInput.style.display = 'none';
                        displaySpan.style.display = 'inline';
                    }
                });
            }

            editorInput.addEventListener('blur', processIdChange);
            editorInput.addEventListener('keypress', function(e) {
                if (e.key === 'Enter') {
                    e.preventDefault();
                    processIdChange();
                }
            });
        }

        // ---------- FILTER BAR ----------
        function initFilterBar() {
            let bar = document.getElementById('filter-bar');
            bar.innerHTML = '';
            if (role === 'admin') {
                bar.innerHTML = `<button class="btn btn-mini btn-outline" onclick="setTimelineFilter('outbox', this)">📤 OUTBOX</button>
                                 <button class="btn btn-mini btn-outline" onclick="setTimelineFilter('printed', this)">🖨️ DATA CETAK</button>`;
            } else if (role === 'designer') {
                bar.innerHTML = `<button class="btn btn-mini btn-outline" onclick="setTimelineFilter('inbox_admin', this)">📥 INBOX (ADMIN)</button>
                                 <button class="btn btn-mini btn-outline" onclick="setTimelineFilter('outbox', this)">📤 OUTBOX</button>
                                 <button class="btn btn-mini btn-outline" onclick="setTimelineFilter('printed', this)">🖨️ DATA CETAK</button>`;
            } else if (role === 'operator') {
                bar.innerHTML = `<button class="btn btn-mini btn-outline" onclick="setTimelineFilter('inbox_designer', this)">📥 INBOX (DESIGNER)</button>
                                 <button class="btn btn-mini btn-outline" onclick="setTimelineFilter('printed', this)">🖨️ DATA CETAK</button>`;
            }
            activateFilterButton();
        }

        function activateFilterButton() {
            let btns = document.querySelectorAll('#filter-bar .btn');
            btns.forEach(btn => btn.classList.remove('active'));
            let targetText = '';
            if (timelineFilter === 'outbox') targetText = 'OUTBOX';
            else if (timelineFilter === 'printed') targetText = 'DATA CETAK';
            else if (timelineFilter === 'inbox_admin') targetText = 'INBOX (ADMIN)';
            else if (timelineFilter === 'inbox_designer') targetText = 'INBOX (DESIGNER)';
            btns.forEach(btn => {
                if (btn.innerText.includes(targetText)) {
                    btn.classList.add('active');
                    btn.style.background = 'var(--fb-blue)';
                    btn.style.color = 'white';
                } else {
                    btn.style.background = 'var(--fb-input)';
                    btn.style.color = 'var(--fb-text)';
                }
            });
        }

        let myLocalIp = 'localhost';

        function setMode(m) {
            if (m === 'local') {
                openKtsPrompt("🖥️ Pengaturan LAN Lokal", "Masukkan kata HOST (Jika ini Server) atau ketik IP Server Partner:", "text", val => {
                    if (val.toUpperCase() === 'HOST') {
                        localStorage.setItem('kts_mode', 'local-host');
                        localStorage.setItem('kts_host_ip', 'localhost');
                        alert(`✅ Mode HOST Lokal Aktif.\nBagikan IP Server Anda ke client.`);
                    } else {
                        localStorage.setItem('kts_mode', 'local-client');
                        localStorage.setItem('kts_host_ip', val);
                    }
                    location.reload();
                });
            } else {
                localStorage.setItem('kts_mode', 'cloud');
                location.reload();
            }
        }

        function initPeer() {
            let mode = localStorage.getItem('kts_mode') || 'cloud';
            let hostIp = localStorage.getItem('kts_host_ip') || 'localhost';
            let opts = {};

            if (mode === 'cloud') {
                opts = { debug: 1 };
            } else {
                opts = {
                    host: hostIp,
                    port: 9000,
                    path: '/Think',
                    secure: false,
                    debug: 1
                };
            }

            peer = new Peer(myId, opts);
            
            peer.on('open', () => {
                updatePeerStatus('ready');
            });

            peer.on('connection', conn => setupConn(conn));
            peer.on('error', err => {
                console.error(err);
                updatePeerStatus('offline');
            });
        }

        function connectMulti() {
            let tid = document.getElementById('target-id').value.trim();
            if (!tid || tid === myId) return alert("⚠️ ID tidak valid!");
            
            if (activeConns.find(c => c.peer === tid)) {
                return alert(`⚠️ Node "${tid}" telah terhubung.`);
            }

            updatePeerStatus('menghubungkan...');
            showToast(`🔌 Mencoba menghubungi ${tid}...`, 'info');
            
            let conn = peer.connect(tid, { reliable: true });
            setupConn(conn);
            document.getElementById('target-id').value = '';
        }

        function setupConn(conn) {
            conn.on('open', () => {
                if (!activeConns.find(c => c.peer === conn.peer)) {
                    activeConns.push(conn);
                    updatePeerUI();
                    playSound('conn-sound');
                    showToast(`⚡ Node tersambung: ${conn.peer}`, 'success');
                }
            });

            conn.on('data', data => {
                if (data.type === 'job') handleIncoming(data, conn.peer);
                if (data.type === 'status_update') handleStatusUpdate(data);
                if (data.type === 'chat') handleIncomingChat(data, conn.peer); 
            });

            conn.on('close', () => {
                activeConns = activeConns.filter(c => c.peer !== conn.peer);
                delete selectedPeersMap[conn.peer];
                updatePeerUI();
            });
        }

        function togglePeerSelection(peerId, isChecked) {
            selectedPeersMap[peerId] = isChecked;
        }

        function updatePeerUI() {
            let html = activeConns.map(c => {
                const isChatOpen = (activeChatPartner === c.peer);
                const unreadCount = unreadChats[c.peer] || 0;
                
                if (selectedPeersMap[c.peer] === undefined) {
                    selectedPeersMap[c.peer] = true;
                }

                const btnLabel = isChatOpen ? '✕ Tutup' : (unreadCount > 0 ? `💬 Obrolan (${unreadCount})` : '💬 Obrolan');
                const btnClass = isChatOpen ? 'btn-outline' : (unreadCount > 0 ? 'btn-danger' : 'btn-primary');

                return `
                <div class="fb-card-panel" style="padding: 8px; margin-bottom: 6px; font-size: 0.8rem; display: flex; flex-direction: column; gap: 6px;">
                    <div style="display: flex; justify-content: space-between; align-items: center; width: 100%;">
                        <div class="contact-row" style="padding: 0; flex: 1;">
                            <div class="online-dot-container">
                                <div class="avatar-circle" style="width:24px; height:24px; font-size:0.7rem;">P</div>
                                <div class="online-dot"></div>
                            </div>
                            <span style="font-weight: 600; text-overflow:ellipsis; overflow:hidden;" title="${c.peer}">${c.peer}</span>
                        </div>
                        <input type="checkbox" id="send-to-${c.peer}" ${selectedPeersMap[c.peer] ? 'checked' : ''} onchange="togglePeerSelection('${c.peer}', this.checked)" style="margin-right:6px; cursor:pointer;">
                    </div>
                    <button class="btn btn-mini ${btnClass}" onclick="toggleInlineChat('${c.peer}')" style="width:100%; font-size:0.7rem; padding:2px;">
                        ${btnLabel}
                    </button>
                    <div id="inline-chat-${c.peer}" style="display: ${isChatOpen ? 'flex' : 'none'}; flex-direction: column; height: 180px; background: var(--fb-input); border-radius: 6px; padding: 6px; gap: 4px;">
                        <div id="chat-messages-${c.peer}" style="flex: 1; overflow-y: auto; display: flex; flex-direction: column; gap: 4px; min-height: 0;"></div>
                        <div style="display: flex; gap: 4px;">
                            <input type="text" id="chat-input-${c.peer}" class="fb-input" style="height: 24px !important; font-size: 0.75rem; padding: 2px 8px;" placeholder="Tulis..." autocomplete="off" onkeydown="if(event.key === 'Enter') sendInlineChatMessage('${c.peer}')">
                            <button class="btn btn-primary btn-mini" onclick="sendInlineChatMessage('${c.peer}')">Kirim</button>
                        </div>
                    </div>
                </div>`;
            }).join('');
            
            document.getElementById('active-conns').innerHTML = html || '<div style="color:var(--fb-text-dim); font-size:0.8rem; text-align:center;">— Tidak ada node aktif —</div>';
            
            activeConns.forEach(c => {
                if (activeChatPartner === c.peer) {
                    renderInlineChatMessages(c.peer);
                }
            });
            
            updatePeerUI();
            updatePeerStatus(activeConns.length ? 'connected' : 'ready');
        }

        function updatePeerStatus(s) {
            let w = document.getElementById('status-widget');
            w.className = activeConns.length ? 'online' : '';
            document.getElementById('status-text').innerText = activeConns.length ? 'TERHUBUNG' : s.toUpperCase();
        }

        // ---------- CONTROL PANEL ----------
        function addNewJob() {
            tempJobs.push({ files: [], inv: '', cap: '', selected: true });
            activeJobIdx = tempJobs.length - 1;
            renderJobs();
        }

        // ---------- RENDER JOBS ----------
        function renderJobs() {
            let list = document.getElementById('job-list');
            list.innerHTML = '';
            tempJobs.forEach((job, jIdx) => {
                let row = document.createElement('div');
                row.className = `job-row ${job.selected ? 'checked' : ''}`;
                let thumbs = job.files.map((f, fIdx) => `<div class="thumb-box" style="position:relative;">
                    <img src="${f.thumb}">${f.isPdf ? '<span class="pdf-tag">PDF</span>' : ''}
                    <div onclick="removeFile(${jIdx},${fIdx})" style="position:absolute; top:-2px; left:-2px; background:var(--danger); color:white; border-radius:50%; width:16px; height:16px; display:flex; align-items:center; justify-content:center; font-size:10px; cursor:pointer;">×</div>
                </div>`).join('');
                row.innerHTML = `
                    <div style="display:flex; justify-content:space-between; margin-bottom:6px;">
                        <span onclick="removeJobRow(${jIdx})" style="background:var(--danger); color:white; padding:1px 6px; border-radius:4px; font-size:0.65rem; cursor:pointer;">HAPUS</span>
                        <input type="checkbox" ${job.selected ? 'checked' : ''} onchange="tempJobs[${jIdx}].selected = this.checked; renderJobs();">
                    </div>
                    <div style="display:flex; flex-wrap:wrap; gap:6px; margin-bottom:6px;">
                        ${thumbs}
                        <div class="thumb-box" style="border:1px dashed var(--fb-blue); display:flex; align-items:center; justify-content:center; font-size:1.2rem; cursor:pointer; color:var(--fb-blue); background:#fff;" onclick="triggerFileSelect(${jIdx})">+</div>
                    </div>
                    <input type="text" class="fb-input" placeholder="No. Invoice" value="${job.inv}" oninput="tempJobs[${jIdx}].inv = this.value" style="margin-bottom:6px; height:32px;">
                    <textarea class="fb-input" placeholder="Tulis instruksi/keterangan disini..." rows="2" oninput="tempJobs[${jIdx}].cap = this.value" style="border-radius:8px; font-size:0.8rem; padding:8px;"></textarea>
                `;

                row.addEventListener('dragover', (e) => {
                    e.preventDefault();
                    row.classList.add('dragover');
                });

                row.addEventListener('dragleave', () => {
                    row.classList.remove('dragover');
                });

                row.addEventListener('drop', async (e) => {
                    e.preventDefault();
                    row.classList.remove('dragover');
                    
                    let files = e.dataTransfer.files;
                    if (files.length > 0) {
                        for (let f of files) {
                            let isPdf = f.type === 'application/pdf';
                            let isImage = f.type.startsWith('image/');
                            if (isPdf || isImage) {
                                let data = await toBase64(f);
                                let thumb = isPdf ? await getPdfPreview(data) : data;
                                job.files.push({ data, thumb, isPdf, name: f.name });
                            }
                        }
                        renderJobs();
                    }
                });

                list.appendChild(row);
            });
        }

        function removeFile(jIdx, fIdx) {
            tempJobs[jIdx].files.splice(fIdx, 1);
            renderJobs();
        }
        function removeJobRow(idx) {
            if (tempJobs.length > 1) {
                tempJobs.splice(idx, 1);
                renderJobs();
            } else alert("⚠️ Minimal satu baris!");
        }
        function triggerFileSelect(idx) {
            activeJobIdx = idx;
            document.getElementById('job-file-in').click();
        }
        async function handleFileSelect(input) {
            if (!input.files.length || activeJobIdx === null) return;
            for (let f of input.files) {
                let isPdf = f.type === 'application/pdf';
                let data = await toBase64(f);
                let thumb = isPdf ? await getPdfPreview(data) : data;
                tempJobs[activeJobIdx].files.push({ data, thumb, isPdf, name: f.name });
            }
            renderJobs();
            input.value = '';
        }
        function toggleSelectAllRows() {
            let all = tempJobs.every(j => j.selected);
            tempJobs.forEach(j => j.selected = !all);
            renderJobs();
        }

        // ---------- MAIN ACTION ----------
        function mainAction() {
            let sel = tempJobs.filter(j => j.selected);
            if (!sel.length) return alert("⚠️ Pilih data!");
            if (role === 'operator') {
                let files = [];
                sel.forEach(j => j.files.forEach(f => files.push({ ...f, inv: j.inv })));
                if (!files.length) return alert("⚠️ Tidak ada file!");
                openPrintLogic({ files, internalId: null });
            } else {
                if (!activeConns.length) return alert("⚠️ Silakan hubungkan Node terlebih dahulu!");
                
                let selectedPeers = activeConns.filter(c => selectedPeersMap[c.peer] !== false);
                if (!selectedPeers.length) return alert("⚠️ Pilih minimal satu node penerima!");

                let d = {
                    type: 'job',
                    jobs: sel,
                    id: Date.now(),
                    senderRole: role,
                    senderId: myId,
                    status: 'pending'
                };
                
                selectedPeers.forEach(c => { if (c.open) c.send(d); });
                
                let outData = { ...d, direction: 'out', to: selectedPeers.map(c => c.peer).join(', '), hidden: false };
                saveStream(outData);
                sel.forEach(job => saveHistory({
                    inv: job.inv,
                    cap: job.cap,
                    fileData: job.files[0] ? job.files[0].thumb : null,
                    isPdf: job.files[0] ? job.files[0].isPdf : false,
                    typeLabel: role === 'admin' ? 'ADM_SEND' : 'DSN_SEND',
                    partner: selectedPeers.map(c => c.peer).join(', ')
                }));
                showToast(`📤 Data berhasil dikirim ke ${selectedPeers.map(c => c.peer).join(', ')}`, 'success');
    
                tempJobs = tempJobs.filter(j => !j.selected);
                if (!tempJobs.length) addNewJob();
                renderJobs();
                let newCard = createMessageCard(outData);
                let area = document.getElementById('stream-area');
                area.insertBefore(newCard, area.firstChild);
            }
        }

        // ---------- INCOMING JOB ----------
        function handleIncoming(data, from) {
            let label = (role === 'designer') ? 'DSN_RECV' : 'OP_RECV';
            let streamData = {
                ...data,
                direction: 'in',
                from: from,
                hidden: false,
                reprintCount: 0,
                status: 'pending'
            };
            saveStream(streamData);
            if (data.jobs) {
                data.jobs.forEach(job => saveHistory({
                    inv: job.inv || '-',
                    cap: job.cap || '-',
                    fileData: job.files[0] ? job.files[0].thumb : null,
                    isPdf: job.files[0] ? job.files[0].isPdf : false,
                    typeLabel: label,
                    partner: from
                }));
            }
            let newCard = createMessageCard(streamData);
            let area = document.getElementById('stream-area');
            area.insertBefore(newCard, area.firstChild);
            playSound('notif-sound');
        }

        // ---------- STATUS UPDATE ----------
        function handleStatusUpdate(d) {
            db.transaction('stream', 'readwrite').objectStore('stream').get(d.msgId).onsuccess = e => {
                let data = e.target.result;
                if (data) {
                    data.status = 'printed';
                    db.transaction('stream', 'readwrite').objectStore('stream').put(data);
                    let idx = streamCache.findIndex(m => m.id === d.msgId);
                    if (idx !== -1) streamCache[idx] = data;
                    updateMessageCardStatus(d.msgId, 'printed', data.reprintCount);
                }
            };
        }

        // ---------- STREAM ----------
        function loadStreamCache() {
            if (!db) return;
            streamCache = [];
            let tx = db.transaction('stream');
            let store = tx.objectStore('stream');
            let req = store.openCursor(null, 'prev');
            let count = 0;
            req.onsuccess = e => {
                let cur = e.target.result;
                if (cur && count < 200) {
                    if (!cur.value.hidden) { streamCache.push(cur.value); count++; }
                    cur.continue();
                } else {
                    renderStream(true);
                }
            };
        }

        function saveStream(o) {
            db.transaction('stream', 'readwrite').objectStore('stream').put(o);
            let idx = streamCache.findIndex(m => m.id === o.id);
            if (idx !== -1) streamCache[idx] = o;
            else {
                streamCache.unshift(o);
                if (streamCache.length > 200) streamCache.pop();
            }
        }

        function renderStream(resetPage = true) {
            let area = document.getElementById('stream-area');
            if (!area) return;
            if (resetPage) {
                timelinePage = 0;
                let searchVal = document.getElementById('timeline-search-input') ? document.getElementById('timeline-search-input').value.trim().toLowerCase() : '';
                
                timelineFilteredData = streamCache.filter(msg => {
                    let categoryMatch = false;
                    if (timelineFilter === 'printed') categoryMatch = msg.status === 'printed';
                    else if (timelineFilter === 'outbox') categoryMatch = msg.senderRole === role && msg.direction === 'out' && msg.status !== 'printed';
                    else if (timelineFilter === 'inbox_admin') categoryMatch = msg.senderRole === 'admin' && msg.direction === 'in' && msg.status !== 'printed';
                    else if (timelineFilter === 'inbox_designer') categoryMatch = msg.senderRole === 'designer' && msg.direction === 'in' && msg.status !== 'printed';
                    
                    if (!categoryMatch) return false;
                    
                    if (searchVal) {
                        if (msg.jobs && msg.jobs.length) {
                            return msg.jobs.some(job => {
                                let invMatch = (job.inv || '').toLowerCase().includes(searchVal);
                                let capMatch = (job.cap || '').toLowerCase().includes(searchVal);
                                return invMatch || capMatch;
                            });
                        }
                        return false;
                    }
                    return true;
                });
                area.innerHTML = '';
            }
            let start = timelinePage * TIMELINE_PAGE_SIZE;
            let end = start + TIMELINE_PAGE_SIZE;
            let pageData = timelineFilteredData.slice(start, end);
            if (!pageData.length) {
                if (timelinePage === 0) area.innerHTML = '<div style="text-align:center; padding:40px; color:var(--fb-text-dim);">📭 Belum ada data timeline</div>';
                return;
            }
            let frag = document.createDocumentFragment();
            pageData.forEach(m => frag.appendChild(createMessageCard(m)));
            if (resetPage) {
                area.innerHTML = '';
                area.appendChild(frag);
            } else {
                let old = area.querySelector('.load-more-container');
                if (old) old.remove();
                area.appendChild(frag);
            }
            if (end < timelineFilteredData.length) {
                let ld = document.createElement('div');
                ld.className = 'load-more-container';
                ld.style.cssText = 'text-align:center; padding:15px;';
                ld.innerHTML = `<button class="btn btn-outline btn-mini" onclick="loadMoreTimeline()">⚡ MUAT LEBIH BANYAK</button>`;
                area.appendChild(ld);
            }
            if (resetPage) area.scrollTop = 0;
        }
        
        function searchTimeline() {
            renderStream(true);
        }

        function loadMoreTimeline() {
            if (isLoadingMore) return;
            isLoadingMore = true;
            timelinePage++;
            renderStream(false);
            isLoadingMore = false;
        }

        // ---------- CREATE FACEBOOK POST CARD ----------
        function createMessageCard(msg) {
            let tmpl = document.getElementById('msg-card-template');
            let card = tmpl.content.cloneNode(true).firstElementChild;
            card.id = `msg-${msg.id}`;
            
            if (selectedInboxes.includes(msg.id)) card.classList.add('selected');

            // Set poster details
            let avatar = card.querySelector('.avatar-circle');
            let nameSpan = card.querySelector('.poster-name');
            let subSpan = card.querySelector('.poster-sub');
            
            let initial = msg.senderRole ? msg.senderRole.substring(0,1).toUpperCase() : 'U';
            avatar.innerText = initial;
            
            if (msg.senderRole === 'admin') avatar.style.background = '#1877f2';
            else if (msg.senderRole === 'designer') avatar.style.background = '#f59e0b';
            else avatar.style.background = '#10b981';

            nameSpan.innerText = `${msg.senderRole ? msg.senderRole.toUpperCase() : 'UNKNOWN'} (${msg.direction === 'out' ? 'Terkirim' : 'Diterima'})`;
            
            let timeStr = new Date(msg.id).toLocaleTimeString('id-ID', {hour:'2-digit', minute:'2-digit'});
            let targetPartner = msg.direction === 'out' ? (msg.to || '?') : (msg.from || 'ME');
            subSpan.innerHTML = `Mitra: ${targetPartner} · ${timeStr} · 🌐`;

            let closeBtn = card.querySelector('.msg-close-trigger');
            closeBtn.onclick = () => hideStream(msg.id);

            // Caption & Image Grid
            let body = card.querySelector('.msg-body');
            let captionDiv = card.querySelector('.msg-body-caption');
            let attachmentDiv = card.querySelector('.asset-attachment-container');
            
            captionDiv.innerHTML = '';
            attachmentDiv.innerHTML = '';

            if (msg.jobs && msg.jobs.length) {
                msg.jobs.forEach((job, jIdx) => {
                    let textInfo = document.createElement('div');
                    textInfo.style.cssText = 'margin-bottom:8px; border-bottom:1px solid var(--fb-border); padding-bottom:6px;';
                    
                    let badgePrint = msg.status === 'printed' ? '<span class="fb-badge fb-badge-success">🖨️ TELAH DICETAK</span>' : '<span class="fb-badge fb-badge-warning">⏳ MENUNGGU</span>';
                    let badgeReprint = msg.reprintCount > 0 ? `<span class="fb-badge fb-badge-blue">🔄 REPRINT ${msg.reprintCount}x</span>` : '';
                    
                    textInfo.innerHTML = `
                        <div style="font-weight:700; color:var(--fb-blue); font-size:0.95rem; margin-bottom:4px;">INV: ${job.inv || '-'}</div>
                        <div style="color:var(--fb-text-dim); font-size:0.85rem; margin-bottom:4px;">${job.cap || '-'}</div>
                        <div>${badgePrint} ${badgeReprint}</div>
                    `;
                    captionDiv.appendChild(textInfo);

                    if (job.files && job.files.length) {
                        job.files.forEach((f, fIdx) => {
                            let imgEl = document.createElement('img');
                            imgEl.src = f.thumb;
                            attachmentDiv.appendChild(imgEl);

                            // Tombol save di dalam attachment
                            let saveBtn = document.createElement('button');
                            saveBtn.className = 'btn btn-mini btn-outline btn-save';
                            saveBtn.style.cssText = 'position:absolute; bottom:8px; right:8px; border-radius:20px;';
                            saveBtn.innerText = '💾 Unduh';
                            saveBtn.dataset.data = f.data;
                            saveBtn.dataset.name = `${job.inv || 'file'}_${fIdx}`;
                            attachmentDiv.appendChild(saveBtn);
                        });
                    }
                });
            }

            let footer = card.querySelector('.msg-footer');
            footer.innerHTML = '';

            if (role === 'designer') {
                if (msg.direction === 'in' && msg.senderRole === 'admin' && msg.status !== 'printed') {
                    let btn = document.createElement('button');
                    btn.className = 'btn btn-primary btn-mini btn-forward';
                    btn.innerText = '📤 TERUSKAN KE OPERATOR';
                    btn.dataset.msgId = msg.id;
                    footer.appendChild(btn);
                }
            } else if (role === 'operator') {
                if (msg.direction === 'in') {
                    if (msg.status !== 'printed') {
                        let printBtn = document.createElement('button');
                        printBtn.className = 'btn btn-success btn-mini btn-print';
                        printBtn.innerText = '🖨️ ANTARKAN KE MESIN';
                        printBtn.dataset.msgId = msg.id;
                        footer.appendChild(printBtn);
                        
                        let selectBtn = document.createElement('button');
                        selectBtn.className = `btn ${selectedInboxes.includes(msg.id) ? 'btn-primary' : 'btn-outline'} btn-mini btn-toggle`;
                        selectBtn.innerText = selectedInboxes.includes(msg.id) ? '✅ SIAP CETAK' : '➕ PILIH BATCH';
                        selectBtn.dataset.msgId = msg.id;
                        footer.appendChild(selectBtn);
                    } else {
                        let reprintBtn = document.createElement('button');
                        reprintBtn.className = 'btn btn-outline btn-mini btn-reprint';
                        reprintBtn.innerText = '🔄 CETAK ULANG (REPRINT)';
                        reprintBtn.dataset.msgId = msg.id;
                        footer.appendChild(reprintBtn);
                    }
                }
            }
            return card;
        }

        // ---------- EVENT DELEGATION ----------
        document.getElementById('stream-area').addEventListener('click', e => {
            if (e.target.classList.contains('btn-save')) {
                downloadAsset(e.target.dataset.data, e.target.dataset.name);
                e.preventDefault();
            }
            if (e.target.classList.contains('btn-print')) {
                openPrintSingle(parseInt(e.target.dataset.msgId));
                e.preventDefault();
            }
            if (e.target.classList.contains('btn-reprint')) {
                openPrintSingle(parseInt(e.target.dataset.msgId));
                e.preventDefault();
            }
            if (e.target.classList.contains('btn-toggle')) {
                toggleSelect(parseInt(e.target.dataset.msgId));
                e.preventDefault();
            }
            if (e.target.classList.contains('btn-forward')) {
                forwardToOperator(parseInt(e.target.dataset.msgId));
                e.preventDefault();
            }
        });

        // ---------- UTILITIES ----------
        function updateStreamContent(id, jIdx, field, val) {
            db.transaction('stream', 'readwrite').objectStore('stream').get(id).onsuccess = e => {
                let d = e.target.result;
                if (d) {
                    d.jobs[jIdx][field] = val;
                    db.transaction('stream', 'readwrite').objectStore('stream').put(d);
                    let idx = streamCache.findIndex(m => m.id === id);
                    if (idx !== -1) streamCache[idx] = d;
                }
            };
        }

        function hideStream(id) {
            db.transaction('stream', 'readwrite').objectStore('stream').get(id).onsuccess = e => {
                let d = e.target.result;
                if (d) {
                    d.hidden = true;
                    db.transaction('stream', 'readwrite').objectStore('stream').put(d);
                    let idx = streamCache.findIndex(m => m.id === id);
                    if (idx !== -1) streamCache.splice(idx, 1);
                    let card = document.getElementById(`msg-${id}`);
                    if (card) card.remove();
                }
            };
        }

        function updateMessageCardStatus(msgId, status, reprint = 0) {
            let card = document.getElementById(`msg-${msgId}`);
            if (!card) return;
            renderStream(true);
        }

        function toggleSelect(id) {
            if (selectedInboxes.includes(id)) selectedInboxes = selectedInboxes.filter(x => x !== id);
            else selectedInboxes.push(id);
            document.getElementById('batch-count').innerText = `${selectedInboxes.length} ITEM ANTRIAN CETAK`;
            let card = document.getElementById(`msg-${id}`);
            if (card) {
                card.classList.toggle('selected', selectedInboxes.includes(id));
                let btn = card.querySelector('.btn-toggle');
                if (btn) {
                    btn.className = `btn ${selectedInboxes.includes(id) ? 'btn-primary' : 'btn-outline'} btn-mini btn-toggle`;
                    btn.innerText = selectedInboxes.includes(id) ? '✅ SIAP' : '➕ BATCH';
                }
            }
        }

        // ---------- FORWARD ----------
        function forwardToOperator(msgId) {
            db.transaction('stream').objectStore('stream').get(msgId).onsuccess = e => {
                let msg = e.target.result;
                if (!msg) return alert('❌ Data tidak ditemukan!');
                if (!activeConns.length) return alert('❌ Silakan hubungkan Node Operator!');
                let fwd = {
                    type: 'job',
                    jobs: msg.jobs,
                    id: Date.now(),
                    senderRole: 'designer',
                    senderId: myId,
                    status: 'pending',
                    originalFrom: msg.senderId
                };
                activeConns.forEach(c => { if (c.open) c.send(fwd); });
                let outData = {
                    ...fwd,
                    direction: 'out',
                    to: activeConns.map(c => c.peer).join(', '),
                    hidden: false,
                    reprintCount: 0,
                    status: 'pending'
                };
                saveStream(outData);
                msg.jobs.forEach(job => saveHistory({
                    inv: job.inv,
                    cap: job.cap,
                    typeLabel: 'DSN_SEND',
                    partner: activeConns.map(c => c.peer).join(', ')
                }));
                showToast('📤 Pekerjaan diteruskan ke Operator!', 'success');
                let card = createMessageCard(outData);
                let area = document.getElementById('stream-area');
                area.insertBefore(card, area.firstChild);
            };
        }

        // ---------- FILTER ----------
        function setTimelineFilter(f, btn) {
            timelineFilter = f;
            document.querySelectorAll('#filter-bar .btn').forEach(b => b.classList.remove('active'));
            if (btn) btn.classList.add('active');
            renderStream(true);
        }

        // ---------- PRINT CONFIG HELPERS ----------
        function getPaperSize() {
            let pp = document.getElementById('p-pdf-paper').value;
            if (pp === 'custom') {
                return {
                    w: parseFloat(document.getElementById('p-custom-w').value) || 21,
                    h: parseFloat(document.getElementById('p-custom-h').value) || 29.7
                };
            }
            let p = pp.split(',');
            return { w: parseFloat(p[0]), h: parseFloat(p[1]) };
        }

        function getMargins() {
            return {
                top: parseFloat(document.getElementById('p-margin-top').value) || 0.5,
                bottom: parseFloat(document.getElementById('p-margin-bottom').value) || 0.5,
                left: parseFloat(document.getElementById('p-margin-left').value) || 0.5,
                right: parseFloat(document.getElementById('p-margin-right').value) || 0.5
            };
        }

        function getLabelPos(paperW, paperH, margins) {
            let maxX = Math.max(0, paperW - margins.left - margins.right);
            let maxY = Math.max(0, paperH - margins.top - margins.bottom);
            let sliderX = parseInt(document.getElementById('p-label-x').value) || 0;
            let sliderY = parseInt(document.getElementById('p-label-y').value) || 0;
            return {
                x: (sliderX / 100) * maxX,
                y: (sliderY / 100) * maxY
            };
        }

        function updatePrintPreview() {
            let paper = getPaperSize();
            let m = getMargins();
            let pos = getLabelPos(paper.w, paper.h, m);
            
            document.getElementById('label-x-val').innerText = pos.x.toFixed(1) + ' cm';
            document.getElementById('label-y-val').innerText = pos.y.toFixed(1) + ' cm';
            
            let showInv = document.getElementById('p-show-inv-label')?.checked ?? true;
            let showMat = document.getElementById('p-show-mat-label')?.checked ?? true;
            
            let dot = document.getElementById('label-preview-dot');
            if (dot) {
                if (!showInv && !showMat) {
                    dot.style.display = 'none';
                } else {
                    dot.style.display = 'block';
                    let txt = '';
                    if (showInv && showMat) txt = 'INV-001 - Chromo';
                    else if (showInv) txt = 'INV-001';
                    else if (showMat) txt = 'Chromo';
                    dot.innerText = txt;
                    
                    let pctX = parseInt(document.getElementById('p-label-x').value) || 0;
                    let pctY = parseInt(document.getElementById('p-label-y').value) || 0;
                    let baseLeft = 10;
                    let baseTop = 10;
                    let rangeW = 60;
                    let rangeH = 20;
                    dot.style.left = (baseLeft + (pctX / 100) * rangeW) + 'px';
                    dot.style.top = (baseTop + (pctY / 100) * rangeH) + 'px';
                }
            }
        }

        // ---------- PRINT ENGINE ----------
        function openPrintSingle(id) {
            db.transaction('stream').objectStore('stream').get(id).onsuccess = e => {
                let d = e.target.result;
                if (!d) return;
                let files = [];
                d.jobs.forEach(j => j.files.forEach(f => files.push({ ...f, inv: j.inv })));
                openPrintLogic({ files, internalId: id, senderId: d.senderId });
            };
        }

        function openPrintLogic(job) {
            activeJob = job;
            document.getElementById('modal-print').style.display = 'flex';
            document.getElementById('p-img').src = job.files[0].thumb;
            document.getElementById('p-pdf-badge').style.display = job.files[0].isPdf ? 'block' : 'none';
            document.getElementById('p-inv-edit').value = job.files[0].inv;

            // Inisialisasi kuantitas individual per foto jika belum ada
            activeJob.files.forEach(f => {
                if (f.printQty === undefined) f.printQty = 1;
            });
            renderIndividualQtys();

            switchPrintMode(job.files[0].isPdf ? 'full' : 'grid');
            resetRotation();
            updatePrintPreview();
        }

        function switchPrintMode(m) {
            currentPrintMode = m;
            document.getElementById('mode-full-btn').className = `btn btn-outline ${m === 'full' ? 'active' : ''}`;
            document.getElementById('mode-grid-btn').className = `btn btn-outline ${m === 'grid' ? 'active' : ''}`;
            document.getElementById('grid-controls').style.display = m === 'grid' ? 'block' : 'none';
            
            // Tampilkan pengaturan quantity individual hanya di mode grid dan terdapat file
            document.getElementById('grid-individual-qtys').style.display = (m === 'grid' && activeJob && activeJob.files && activeJob.files.length > 0) ? 'block' : 'none';
            
            calcGrid();
        }

        function renderIndividualQtys() {
            let container = document.getElementById('grid-individual-list');
            if (!container || !activeJob) return;
            container.innerHTML = '';
            activeJob.files.forEach((f, idx) => {
                let div = document.createElement('div');
                div.style.cssText = 'display:flex; align-items:center; gap:10px; background:var(--fb-card); padding:6px; border-radius:6px; border:1px solid var(--fb-border);';
                div.innerHTML = `
                    <div style="width:40px; height:40px; background:#000; border-radius:4px; overflow:hidden; display:flex; align-items:center; justify-content:center; border:1px solid var(--fb-border);">
                        <img src="${f.thumb}" style="max-width:100%; max-height:100%; object-fit:contain;">
                    </div>
                    <div style="flex:1; font-size:0.75rem; font-weight:600; text-overflow:ellipsis; overflow:hidden; white-space:nowrap; color:var(--fb-text);">
                        ${f.name || `Foto ${idx+1}`}
                    </div>
                    <div style="display:flex; align-items:center; gap:6px;">
                        <label style="font-size:0.7rem; font-weight:bold; color:var(--fb-text-dim);">QTY (pcs):</label>
                        <input type="number" min="0" value="${f.printQty}" class="fb-input" style="width:65px; text-align:center; padding:4px;" 
                               oninput="activeJob.files[${idx}].printQty = Math.max(0, parseInt(this.value) || 0); calcGrid();">
                    </div>
                `;
                container.appendChild(div);
            });
        }

        // FUNGSI BAGI RATA KUANTITAS FOTO SECARA OTOMATIS KE DALAM 1 LEMBAR KERTAS
        function autoDistributeQtys() {
            if (!activeJob || !activeJob.files || activeJob.files.length === 0) {
                showToast("Tidak ada foto untuk dibagi!", "error");
                return;
            }
            
            let pw, ph, pp = document.getElementById('p-pdf-paper').value;
            if (pp === 'custom') { 
                pw = parseFloat(document.getElementById('p-custom-w').value) || 0; 
                ph = parseFloat(document.getElementById('p-custom-h').value) || 0; 
            } else { 
                let p = pp.split(','); 
                pw = parseFloat(p[0]); 
                ph = parseFloat(p[1]); 
            }
            let m = getMargins();
            let contentW = pw - m.left - m.right;
            let contentH = ph - m.top - m.bottom;

            let w = parseFloat(document.getElementById('p-grid-w').value) || 1;
            let h = parseFloat(document.getElementById('p-grid-h').value) || 1;
            let gap = parseFloat(document.getElementById('p-grid-gap').value) || 0;
            
            let nx = Math.floor((contentW + gap) / (w + gap));
            let ny = Math.floor((contentH + gap) / (h + gap));
            let capacity = nx * ny;
            
            if (capacity <= 0) {
                showToast("Ukuran grid terlalu besar untuk kertas!", "error");
                return;
            }
            
            let numFiles = activeJob.files.length;
            let baseQty = Math.floor(capacity / numFiles);
            let remainder = capacity % numFiles;
            
            // Bagi rata kuantitas dan sisipkan remainder sisa ke index-index awal secara adil
            activeJob.files.forEach((f, idx) => {
                f.printQty = baseQty + (idx < remainder ? 1 : 0);
            });
            
            renderIndividualQtys();
            calcGrid();
            showToast("⚡ Kuantitas berhasil dibagi rata dalam 1 lembar!", "success");
        }
        
        function rotatePreviewImage() {
            currentRotation = (currentRotation + 90) % 360;
            const img = document.getElementById('p-img');
            img.style.transform = `rotate(${currentRotation}deg)`;
            
            if (currentPrintMode === 'grid') {
                let wInput = document.getElementById('p-grid-w');
                let hInput = document.getElementById('p-grid-h');
                let tempW = wInput.value;
                wInput.value = hInput.value;
                hInput.value = tempW;
                calcGrid();
            }
            
            showToast(`🔄 Rotasi pratinjau: ${currentRotation}°`, 'info');
        }

        function resetRotation() {
            currentRotation = 0;
            const img = document.getElementById('p-img');
            if (img) img.style.transform = 'rotate(0deg)';
        }

        async function rotateImageData(imageDataUrl, degrees) {
            if (degrees === 0 || degrees === 360) return imageDataUrl;
            
            return new Promise((resolve, reject) => {
                const img = new Image();
                img.onload = () => {
                    const canvas = document.createElement('canvas');
                    const ctx = canvas.getContext('2d');
                    
                    if (degrees === 90 || degrees === 270) {
                        canvas.width = img.height;
                        canvas.height = img.width;
                    } else {
                        canvas.width = img.width;
                        canvas.height = img.height;
                    }
                    
                    ctx.save();
                    ctx.translate(canvas.width / 2, canvas.height / 2);
                    ctx.rotate(degrees * Math.PI / 180);
                    ctx.drawImage(img, -img.width / 2, -img.height / 2);
                    ctx.restore();
                    
                    resolve(canvas.toDataURL('image/jpeg', 0.95));
                };
                img.onerror = reject;
                img.src = imageDataUrl;
            });
        }

        function toggleCustomPaper(v) {
            document.getElementById('custom-paper-box').style.display = v === 'custom' ? 'flex' : 'none';
            calcGrid();
            updatePrintPreview();
        }

        function calcGrid() {
            if (currentPrintMode !== 'grid') { 
                document.getElementById('grid-res-box').innerText = 'SATU HALAMAN PENUH'; 
                return; 
            }
            let pw, ph, pp = document.getElementById('p-pdf-paper').value;
            if (pp === 'custom') { 
                pw = parseFloat(document.getElementById('p-custom-w').value) || 0; 
                ph = parseFloat(document.getElementById('p-custom-h').value) || 0; 
            } else { 
                let p = pp.split(','); 
                pw = parseFloat(p[0]); 
                ph = parseFloat(p[1]); 
            }
            let m = getMargins();
            let contentW = pw - m.left - m.right;
            let contentH = ph - m.top - m.bottom;

            let w = parseFloat(document.getElementById('p-grid-w').value) || 1;
            let h = parseFloat(document.getElementById('p-grid-h').value) || 1;
            let gap = parseFloat(document.getElementById('p-grid-gap').value) || 0;
            
            let nx = Math.floor((contentW + gap) / (w + gap));
            let ny = Math.floor((contentH + gap) / (h + gap));
            let capacity = nx * ny;

            let totalItems = 0;
            if (activeJob && activeJob.files) {
                totalItems = activeJob.files.reduce((sum, f) => sum + (parseInt(f.printQty) || 0), 0);
            }

            if (capacity > 0) {
                let sheetsNeeded = Math.ceil(totalItems / capacity);
                document.getElementById('grid-res-box').innerText = `📐 Kapasitas: ${capacity} pcs/lembar | Total Item: ${totalItems} pcs | Butuh: ${sheetsNeeded} Lembar`;
                
                // Perbarui otomatis QTY Lembar penerbitan di formulir
                let targetInput = document.getElementById('p-pdf-target');
                if (targetInput) {
                    targetInput.value = sheetsNeeded > 0 ? sheetsNeeded : 1;
                }
            } else {
                document.getElementById('grid-res-box').innerText = `📐 Ukuran grid terlalu besar untuk kertas ini!`;
            }
        }

        async function physicalRotate() {
            let f = activeJob.files[0];
            if (f.isPdf) return;
            let img = new Image();
            img.src = f.data;
            await img.decode();
            let cvs = document.createElement('canvas');
            cvs.width = img.height;
            cvs.height = img.width;
            let ctx = cvs.getContext('2d');
            ctx.translate(cvs.width / 2, cvs.height / 2);
            ctx.rotate(90 * Math.PI / 180);
            ctx.drawImage(img, -img.width / 2, -img.height / 2);
            f.data = f.thumb = cvs.toDataURL('image/jpeg', 0.9);
            document.getElementById('p-img').src = f.thumb;
            let ow = document.getElementById('p-grid-w').value;
            document.getElementById('p-grid-w').value = document.getElementById('p-grid-h').value;
            document.getElementById('p-grid-h').value = ow;
            calcGrid();
        }

        function executePrint() {
            if (currentPrintMode === 'full') executeFullPrint();
            else executeGridPrint();
        }

        async function executeFullPrint() {
            let btn = document.getElementById('btn-do-print');
            btn.innerText = 'RERENDERING...';
            btn.disabled = true;
            try {
                let paper = getPaperSize();
                let pw = paper.w, ph = paper.h;
                let m = getMargins();
                let pos = getLabelPos(pw, ph, m);
                let target = parseInt(document.getElementById('p-pdf-target').value) || 1;
                let mat = document.getElementById('p-mat').value;
                let inv = document.getElementById('p-inv-edit').value;

                let contentW = pw - m.left - m.right;
                let contentH = ph - m.top - m.bottom;

                let showInv = document.getElementById('p-show-inv-label')?.checked ?? true;
                let showMat = document.getElementById('p-show-mat-label')?.checked ?? true;
                let labelText = '';
                if (showInv && showMat) labelText = `${inv} - ${mat}`;
                else if (showInv) labelText = inv;
                else if (showMat) labelText = mat;

                let labelHtml = labelText ? `<div class="inv-label-top">${labelText}</div>` : '';

                let html = `<style>
                    @page { size: ${pw}cm ${ph}cm; margin:0; }
                    body { margin:0; padding:0; }
                    .sheet { 
                        width: ${pw}cm; 
                        height: ${ph}cm; 
                        page-break-after:always; 
                        position:relative; 
                        box-sizing:border-box;
                        overflow:hidden;
                    }
                    .content-area {
                        position: absolute;
                        top: ${m.top}cm;
                        left: ${m.left}cm;
                        width: ${contentW}cm;
                        height: ${contentH}cm;
                        display: flex;
                        align-items: center;
                        justify-content: center;
                    }
                    .p-img { 
                        max-width: 100%; 
                        max-height: 100%; 
                        object-fit: contain; 
                    }
                    .inv-label-top {
                        position: absolute;
                        top: ${m.top + pos.y}cm;
                        left: ${m.left + pos.x}cm;
                        font-size: 10pt;
                        font-family: 'Outfit', sans-serif;
                        font-weight: 700;
                        color: #000;
                        background: rgba(255,255,255,0.95);
                        padding: 2px 10px;
                        border-radius: 4px;
                        white-space: nowrap;
                        z-index: 100;
                        box-shadow: 0 1px 4px rgba(0,0,0,0.3);
                    }
                </style>`;

                let content = '';
                for (let f of activeJob.files) {
                    let img = f.isPdf ? await getPdfPreview(f.data, true) : f.data;
                    let rotatedImg = await rotateImageData(img, currentRotation);
                    for (let i = 0; i < target; i++) {
                        content += `<div class="sheet">
                            <div class="content-area"><img src="${rotatedImg}" class="p-img"></div>
                            ${labelHtml}
                        </div>`;
                    }
                }
                finishPrint(html + content, inv, target, 'FULL PAGE');
            } catch (e) {
                alert('❌ Gagal render! ' + e.message);
                btn.innerText = 'MULAI CETAK';
                btn.disabled = false;
            }
        }

        async function executeGridPrint() {
            let btn = document.getElementById('btn-do-print');
            btn.innerText = 'PROSES GRID...';
            btn.disabled = true;
            try {
                let paper = getPaperSize();
                let pw = paper.w, ph = paper.h;
                let m = getMargins();
                let pos = getLabelPos(pw, ph, m);
                
                let w = parseFloat(document.getElementById('p-grid-w').value);
                let h = parseFloat(document.getElementById('p-grid-h').value);
                let gap = parseFloat(document.getElementById('p-grid-gap').value) || 0;
                let inv = document.getElementById('p-inv-edit').value;
                let mat = document.getElementById('p-mat').value;
                
                let kt = parseFloat(document.getElementById('p-grid-kres-thick').value) || 0.2;
                let kl = parseFloat(document.getElementById('p-grid-kres-len').value) || 5;
                let ko = parseFloat(document.getElementById('p-grid-kres-offset')?.value || 0);
                let showKres = document.getElementById('p-grid-show-kres')?.checked ?? true;

                let showInv = document.getElementById('p-show-inv-label')?.checked ?? true;
                let showMat = document.getElementById('p-show-mat-label')?.checked ?? true;
                let labelText = '';
                if (showInv && showMat) labelText = `${inv} - ${mat}`;
                else if (showInv) labelText = inv;
                else if (showMat) labelText = mat;

                let labelHtml = labelText ? `<div class="inv-label-top">${labelText}</div>` : '';

                let contentW = pw - m.left - m.right;
                let contentH = ph - m.top - m.bottom;

                let nx = Math.floor((contentW + gap) / (w + gap));
                let ny = Math.floor((contentH + gap) / (h + gap));
                let capacity = nx * ny;

                if (capacity <= 0) {
                    throw new Error("Ukuran area cetak kertas terlalu kecil untuk memuat satu grid.");
                }

                // Kumpulkan seluruh sel foto berdasarkan kuantitas masing-masing
                let flatCells = [];
                let safeRotation = (typeof currentRotation === 'number') ? currentRotation : 0;

                for (let f of activeJob.files) {
                    let qty = parseInt(f.printQty);
                    if (isNaN(qty) || qty <= 0) continue;

                    let imgSource = f.isPdf ? await getPdfPreview(f.data, true) : f.data;
                    let rotatedData = await rotateImageData(imgSource, safeRotation);

                    for (let q = 0; q < qty; q++) {
                        flatCells.push(rotatedData);
                    }
                }

                if (flatCells.length === 0) {
                    throw new Error("Kuantitas semua foto adalah 0. Masukkan setidaknya 1 kuantitas untuk mencetak.");
                }

                // Hitung jumlah lembar yang dibutuhkan untuk memuat total campuran item
                let totalSheets = Math.ceil(flatCells.length / capacity);

                let html = `<style>
                    @page { size: ${pw}cm ${ph}cm; margin:0; }
                    body { margin:0; padding:0; }
                    .sheet { 
                        width: ${pw}cm; 
                        height: ${ph}cm; 
                        page-break-after:always; 
                        position:relative; 
                        overflow:hidden;
                        box-sizing:border-box;
                    }
                    .grid-wrapper {
                        position: absolute;
                        top: ${m.top}cm;
                        left: ${m.left}cm;
                        width: ${contentW}cm;
                        height: ${contentH}cm;
                        display: flex;
                        align-items: center;
                        justify-content: center;
                    }
                    .grid-container { 
                        display:grid; 
                        grid-template-columns:repeat(${nx}, ${w}cm); 
                        grid-gap:${gap}cm; 
                        position:relative; 
                    }
                    .cell { 
                        position:relative; 
                        width:${w}cm; 
                        height:${h}cm; 
                        overflow:visible;
                    }
                    .cell img { width:100%; height:100%; object-fit:fill; }

                    .crop-mark {
                        position: absolute;
                        width: var(--crop-len);
                        height: var(--crop-len);
                        pointer-events: none;
                        z-index: 25;
                        -webkit-print-color-adjust: exact !important;
                        print-color-adjust: exact !important;
                    }
                    .crop-mark.tl {
                        top: calc(-1 * var(--crop-offset));
                        left: calc(-1 * var(--crop-offset));
                        border-top: var(--crop-thick) solid #000;
                        border-left: var(--crop-thick) solid #000;
                    }
                    .crop-mark.tr {
                        top: calc(-1 * var(--crop-offset));
                        right: calc(-1 * var(--crop-offset));
                        border-top: var(--crop-thick) solid #000;
                        border-right: var(--crop-thick) solid #000;
                    }
                    .crop-mark.bl {
                        bottom: calc(-1 * var(--crop-offset));
                        left: calc(-1 * var(--crop-offset));
                        border-bottom: var(--crop-thick) solid #000;
                        border-left: var(--crop-thick) solid #000;
                    }
                    .crop-mark.br {
                        bottom: calc(-1 * var(--crop-offset));
                        right: calc(-1 * var(--crop-offset));
                        border-bottom: var(--crop-thick) solid #000;
                        border-right: var(--crop-thick) solid #000;
                    }

                    .inv-label-top {
                        position: absolute;
                        top: ${m.top + pos.y}cm;
                        left: ${m.left + pos.x}cm;
                        font-size: 10pt;
                        font-family: 'Outfit', sans-serif;
                        font-weight: 700;
                        color: #000;
                        background: rgba(255,255,255,0.95);
                        padding: 2px 10px;
                        border-radius: 4px;
                        white-space: nowrap;
                        z-index: 100;
                        box-shadow: 0 1px 4px rgba(0,0,0,0.3);
                    }
                </style>`;

                let marksHtml = '';
                if (showKres) {
                    marksHtml = `
                        <div class="crop-mark tl"></div>
                        <div class="crop-mark tr"></div>
                        <div class="crop-mark bl"></div>
                        <div class="crop-mark br"></div>
                    `;
                }

                let content = '';
                for (let s = 0; s < totalSheets; s++) {
                    let cellsHtml = '';
                    let startIdx = s * capacity;
                    let endIdx = Math.min(startIdx + capacity, flatCells.length);

                    for (let i = startIdx; i < endIdx; i++) {
                        cellsHtml += `
                            <div class="cell" style="--crop-len:${kl}mm; --crop-thick:${kt}mm; --crop-offset:${ko}mm;">
                                <img src="${flatCells[i]}">
                                ${marksHtml}
                            </div>`;
                    }

                    content += `<div class="sheet">
                        <div class="grid-wrapper"><div class="grid-container">${cellsHtml}</div></div>
                        ${labelHtml}
                    </div>`;
                }
                
                finishPrint(html + content, inv, totalSheets, `GRID MIXED (Total: ${flatCells.length} pcs)`);
            } catch (e) {
                alert('❌ Gagal render grid! Error: ' + e.message);
                btn.innerText = 'MULAI CETAK';
                btn.disabled = false;
            }
        }

        function finishPrint(fullHtml, inv, qty, mode) {
            let f = document.getElementById('p-frame');
            f.style.display = 'block';
            f.contentWindow.document.open();
            f.contentWindow.document.write(fullHtml);
            f.contentWindow.document.close();

            setTimeout(() => {
                f.contentWindow.print();
                f.style.display = 'none';
                document.getElementById('btn-do-print').innerText = 'MULAI CETAK';
                document.getElementById('btn-do-print').disabled = false;

                if (activeJob.internalId) {
                    db.transaction('stream', 'readwrite').objectStore('stream').get(activeJob.internalId).onsuccess = e => {
                        let d = e.target.result;
                        if (!d) return;
                        let previousStatus = d.status;
                        let isLocalJob = (d.from === 'LOKAL (MANUAL)' || d.senderId === myId);
                        if (d.status === 'printed') {
                            d.reprintCount = (d.reprintCount || 0) + 1;
                        } else {
                            d.status = 'printed';
                            d.reprintCount = 0;
                        }
                        db.transaction('stream', 'readwrite').objectStore('stream').put(d).onsuccess = () => {
                            let idx = streamCache.findIndex(m => m.id === activeJob.internalId);
                            if (idx !== -1) {
                                streamCache[idx].status = d.status;
                                streamCache[idx].reprintCount = d.reprintCount;
                            }
                            updateMessageCardStatus(activeJob.internalId, d.status, d.reprintCount);
                            if (!isLocalJob && previousStatus !== 'printed') {
                                let card = document.getElementById(`msg-${activeJob.internalId}`);
                                if (card) card.remove();
                            }
                            if (timelineFilter === 'printed' && previousStatus !== 'printed') {
                                let newCard = createMessageCard(d);
                                let area = document.getElementById('stream-area');
                                area.insertBefore(newCard, area.firstChild);
                            }
                            showToast(`🖨️ Cetak berhasil${previousStatus === 'printed' ? ' (Reprint)' : ''}`, 'success');
                        };
                    };
                    let conn = activeConns.find(x => x.peer === activeJob.senderId);
                    if (conn && activeJob.senderId && activeJob.senderId !== myId) {
                        conn.send({ type: 'status_update', msgId: activeJob.internalId });
                    }
                }
                else if (role === 'operator') {
                    let existingLocalJob = streamCache.find(msg =>
                        msg.from === 'LOKAL (MANUAL)' &&
                        msg.jobs && msg.jobs[0] &&
                        msg.jobs[0].inv === inv &&
                        msg.jobs[0].files && msg.jobs[0].files[0] &&
                        msg.jobs[0].files[0].data === activeJob.files[0].data
                    );
                    if (existingLocalJob) {
                        existingLocalJob.reprintCount = (existingLocalJob.reprintCount || 0) + 1;
                        existingLocalJob.status = 'printed';
                        db.transaction('stream', 'readwrite').objectStore('stream').put(existingLocalJob);
                        let idx = streamCache.findIndex(m => m.id === existingLocalJob.id);
                        if (idx !== -1) streamCache[idx] = existingLocalJob;
                        updateMessageCardStatus(existingLocalJob.id, 'printed', existingLocalJob.reprintCount);
                        showToast(`🔄 Cetak ulang untuk invoice ${inv}`, 'success');
                    } else {
                        let localJob = {
                            id: Date.now(),
                            direction: 'in',
                            from: 'LOKAL (MANUAL)',
                            senderRole: 'operator',
                            senderId: myId,
                            status: 'printed',
                            reprintCount: 0,
                            jobs: [{ inv, cap: mode, files: activeJob.files }],
                            hidden: false
                        };
                        saveStream(localJob);
                        showToast('✅ Cetak selesai! Disimpan ke Data Cetak.', 'success');
                        if (timelineFilter === 'printed') {
                            let newCard = createMessageCard(localJob);
                            let area = document.getElementById('stream-area');
                            area.insertBefore(newCard, area.firstChild);
                        }
                    }
                }

                saveHistory({
                    inv,
                    typeLabel: 'PRODUKSI_SELESAI',
                    qty,
                    cap: mode,
                    fileData: activeJob.files[0] ? activeJob.files[0].thumb : null,
                    isPdf: activeJob.files[0] ? activeJob.files[0].isPdf : false,
                    partner: activeJob.internalId ? activeJob.senderId : 'MANUAL'
                });

                playSound('done-sound');
                closeModal();
            }, 1000);
        }

        function closeModal() {
            document.querySelectorAll('.modal').forEach(m => m.style.display = 'none');
            resetRotation();
        }

        // ---------- BATCH PRINT ----------
        function openBatchPrint() {
            if (!selectedInboxes.length) return alert('⚠️ Pilih item batch!');
            let allFiles = [], count = 0;
            selectedInboxes.forEach(id => {
                db.transaction('stream').objectStore('stream').get(id).onsuccess = e => {
                    e.target.result.jobs.forEach(j => j.files.forEach(f => { if (f.isPdf) allFiles.push({ ...f, inv: j.inv }); }));
                    count++;
                    if (count === selectedInboxes.length) openPrintLogic({ files: allFiles, internalId: null });
                };
            });
        }

        // ---------- HISTORY ----------
        function saveHistory(obj) {
            db.transaction('history', 'readwrite').objectStore('history').add({
                time: new Date().toLocaleString('id-ID'),
                fileData: obj.fileData || null,
                isPdf: obj.isPdf || false,
                inv: obj.inv || '-',
                cap: obj.cap || '-',
                partner: obj.partner || '?',
                typeLabel: obj.typeLabel,
                role: role,
                qty: obj.qty || 1
            });
            trimHistory();
        }

        function trimHistory() {
            if (!db) return;
            let tx = db.transaction('history', 'readwrite');
            let store = tx.objectStore('history');
            store.count().onsuccess = e => {
                if (e.target.result > 1000) {
                    store.openCursor().onsuccess = ev => {
                        let cur = ev.target.result, del = 0;
                        while (cur && del < 200) {
                            store.delete(cur.primaryKey);
                            cur.continue();
                            del++;
                        }
                    };
                }
            };
        }

        function filterHistoryTable() {
            let textInput = document.getElementById('hist-search-input');
            let dateInput = document.getElementById('hist-search-date');
            
            let textFilter = textInput.value.toUpperCase();
            let dateFilter = dateInput.value;

            let dateMatchString = "";
            if (dateFilter) {
                let parts = dateFilter.split('-');
                dateMatchString = `${parts[2]}/${parts[1]}/${parts[0]}`; 
            }

            let tbody = document.getElementById('hist-body');
            let tr = tbody.getElementsByTagName('tr');

            for (let i = 0; i < tr.length; i++) {
                if(tr[i].innerText.includes("Belum ada data")) continue;
                
                let tdTime    = tr[i].getElementsByTagName('td')[0];
                let tdPartner = tr[i].getElementsByTagName('td')[3];
                let tdInv     = tr[i].getElementsByTagName('td')[4];
                let tdCap     = tr[i].getElementsByTagName('td')[5];

                if (tdTime && tdInv) {
                    let textContent = (tdPartner.innerText + " " + tdInv.innerText + " " + tdCap.innerText).toUpperCase();
                    let textMatch = textContent.indexOf(textFilter) > -1;

                    let timeContent = tdTime.innerText;
                    let dateMatch = true;

                    if (dateFilter) {
                        let d = parseInt(dateFilter.split('-')[2]);
                        let m = parseInt(dateFilter.split('-')[1]);
                        let y = dateFilter.split('-')[0];
                        
                        let check1 = `${d}/${m}/${y}`;
                        let check2 = dateMatchString;
                        
                        if (timeContent.includes(check1) || timeContent.includes(check2)) {
                            dateMatch = true;
                        } else {
                            dateMatch = false;
                        }
                    }

                    if (textMatch && dateMatch) {
                        tr[i].style.display = "";
                    } else {
                        tr[i].style.display = "none";
                    }
                }       
            }
        }

        function refreshHistBody() {
            let tbody = document.getElementById('hist-body');
            tbody.innerHTML = '';
            let statusMap = {
                'ADM_SEND': 'Admin → Designer',
                'DSN_RECV': 'Admin → Designer',
                'DSN_SEND': 'Designer → Operator',
                'OP_RECV': 'Designer → Operator',
                'PRODUKSI_SELESAI': '',
                'OP_PROD': '',
                'OP_LAYOUTER_PROD': 'Hasil Layouter'
            };
            db.transaction('history').objectStore('history').getAll().onsuccess = e => {
                let all = e.target.result.reverse();
                let rendered = 0, MAX = 100;
                all.forEach(h => {
                    let show = false;
                    if (role === 'admin' && h.typeLabel === 'ADM_SEND') show = true;
                    else if (role === 'designer') {
                        if (currentTab === 1 && h.typeLabel === 'DSN_RECV') show = true;
                        if (currentTab === 2 && h.typeLabel === 'DSN_SEND') show = true;
                    } else if (role === 'operator') {
                        if (currentTab === 1 && h.typeLabel === 'OP_RECV') show = true;
                        if (currentTab === 2 && (h.typeLabel === 'PRODUKSI_SELESAI' || h.typeLabel === 'OP_PROD')) show = true;
                        if (currentTab === 3 && h.typeLabel === 'OP_LAYOUTER_PROD') show = true;
                    }
                    if (!show || rendered >= MAX) return;
                    let row = tbody.insertRow();
                    row.style.fontSize = '0.8rem';
                    row.insertCell().innerHTML = h.time || '';
                    let fileCell = row.insertCell();
                    if (h.fileData) {
                        fileCell.innerHTML = `<div style="width:36px; height:36px; background:#000; border-radius:4px; overflow:hidden; cursor:pointer; border:1px solid var(--fb-border);" onclick="downloadAsset('${h.fileData}', '${h.inv}.png')">
                            <img src="${h.fileData}" style="width:100%; height:100%; object-fit:cover;">
                        </div>`;
                    } else {
                        fileCell.innerHTML = '<span style="color:var(--fb-text-dim)">-</span>';
                    }
                    let statusCell = row.insertCell();
                    statusCell.innerHTML = (h.typeLabel === 'PRODUKSI_SELESAI' || h.typeLabel === 'OP_PROD' || h.typeLabel === 'OP_LAYOUTER_PROD') ? (statusMap[h.typeLabel] || '') : (statusMap[h.typeLabel] || h.typeLabel);
                    let partnerCell = row.insertCell();
                    partnerCell.innerHTML = (h.typeLabel === 'PRODUKSI_SELESAI' || h.typeLabel === 'OP_PROD' || h.typeLabel === 'OP_LAYOUTER_PROD') ? '' : (h.partner || '?');
                    row.insertCell().innerHTML = `<span style="color:var(--fb-blue); font-weight:700;">${h.inv || '-'}</span>`;
                    row.insertCell().innerHTML = `<div style="color:var(--fb-text-dim);">${h.cap || ''}</div>`;
                    let qtyCell = row.insertCell();
                    qtyCell.innerHTML = (h.typeLabel === 'PRODUKSI_SELESAI' || h.typeLabel === 'OP_PROD' || h.typeLabel === 'OP_LAYOUTER_PROD') ? `<span style="color:var(--success); font-weight:800;">${h.qty || 1}</span>` : '';
                    let aksiCell = row.insertCell();
                    aksiCell.innerHTML = `<button class="btn btn-mini btn-danger btn-outline" style="border:none;" onclick="deleteHistory(${h.id})">Del</button>`;
                    rendered++;
                });
                if (rendered === 0) tbody.innerHTML = `<tr><td colspan="8" style="padding:20px; text-align:center; color:var(--fb-text-dim);">📭 Belum ada rekaman log historis</td></tr>`;
            };
        }

        function switchHistTab(n) {
            currentTab = n;
            let searchInput = document.getElementById('hist-search-input');
            if(searchInput) searchInput.value = ''; 
            let dateInput = document.getElementById('hist-search-date');
            if(dateInput) dateInput.value = ''; 
            
            document.getElementById('tab-1').classList.toggle('active', n === 1);
            document.getElementById('tab-2').classList.toggle('active', n === 2);
            document.getElementById('tab-3').classList.toggle('active', n === 3);
            
            refreshHistBody();
        }

        // ---------- HIST TAB TOGGLE ----------
        function toggleHistory() {
            let m = document.getElementById('modal-hist');
            m.style.display = m.style.display === 'flex' ? 'none' : 'flex';
            if (m.style.display === 'flex') {
                document.getElementById('hist-role-title').innerText = role.toUpperCase();
                let tab3 = document.getElementById('tab-3');
                if (role === 'operator') {
                    tab3.style.display = 'block';
                } else {
                    tab3.style.display = 'none';
                }
                switchHistTab(1);
            }
        }

        function deleteHistory(id) {
            db.transaction('history', 'readwrite').objectStore('history').delete(id).onsuccess = () => refreshHistBody();
        }

        function clearAllHistory() {
            if (confirm('🗑️ Hapus seluruh laporan log?')) {
                let tx = db.transaction('history', 'readwrite');
                tx.objectStore('history').openCursor().onsuccess = e => {
                    let c = e.target.result;
                    if (c && c.value.role === role) c.delete();
                    c?.continue();
                };
                setTimeout(refreshHistBody, 300);
            }
        }

        async function exportLogToPDF() {
            const { jsPDF } = window.jspdf;
            const doc = new jsPDF();
            doc.text(`THINK FLOW - PRODUCTION LOG (${role.toUpperCase()})`, 14, 15);
            const table = document.getElementById('hist-table-real');
            const headers = [];
            const headerCells = table.querySelectorAll('thead tr th');
            for (let i = 0; i < headerCells.length - 1; i++) headers.push(headerCells[i].innerText);
            const rows = [];
            const bodyRows = table.querySelectorAll('tbody tr');
            bodyRows.forEach(row => {
                let rowData = [];
                let cells = row.querySelectorAll('td');
                for (let i = 0; i < cells.length - 1; i++) rowData.push(cells[i].innerText);
                rows.push(rowData);
            });
            doc.autoTable({
                head: [headers],
                body: rows,
                margin: { top: 25 },
                styles: { fontSize: 8 },
                headStyles: { fillColor: [24, 119, 242] }
            });
            doc.save('log_Think.pdf');
        }

        // ---------- UTILS ----------
        async function getPdfPreview(b64, high = false) {
            try {
                let pdf = await pdfjsLib.getDocument({ data: atob(b64.split(',')[1]) }).promise;
                let page = await pdf.getPage(1);
                let viewport = page.getViewport({ scale: high ? 3.0 : 0.5 });
                let canvas = document.createElement('canvas');
                canvas.height = viewport.height;
                canvas.width = viewport.width;
                await page.render({ canvasContext: canvas.getContext('2d'), viewport }).promise;
                return canvas.toDataURL('image/jpeg', high ? 0.9 : 0.5);
            } catch (e) {
                return null;
            }
        }

        // ---------- LAYOUTER PRINT CONFIGURATION MODALS ----------
        function openLayoutPrintModal() {
            if (!canvasItems.length) return alert('⚠️ Canvas kosong!');
            document.getElementById('modal-layout-print').style.display = 'flex';
        }

        function closeLayoutPrintModal() {
            document.getElementById('modal-layout-print').style.display = 'none';
        }

        function executeLayoutPrint() {
            if (!canvasItems.length) return alert('⚠️ Canvas kosong!');
            let dim = document.getElementById('m-paper').value.split(',');
            let pw = parseFloat(dim[0]), ph = parseFloat(dim[1]);
            
            let useKres = document.getElementById('l-use-kres').checked;
            
            let tebal = parseFloat(document.getElementById('l-kres-tebal').value);
            if (isNaN(tebal)) tebal = 0.3;
            let panjang = parseFloat(document.getElementById('l-kres-panjang').value);
            if (isNaN(panjang)) panjang = 5;
            let offset = parseFloat(document.getElementById('l-kres-offset').value);
            if (isNaN(offset)) offset = 0;
            
            let inv = document.getElementById('l-inv').value.trim() || 'LAY-001';
            let mat = document.getElementById('l-mat').value;
            let qty = parseInt(document.getElementById('l-qty').value);
            if (isNaN(qty) || qty < 1) qty = 1;
            
            let m = {
                top: parseFloat(document.getElementById('l-margin-top').value),
                bottom: parseFloat(document.getElementById('l-margin-bottom').value),
                left: parseFloat(document.getElementById('l-margin-left').value),
                right: parseFloat(document.getElementById('l-margin-right').value)
            };
            if (isNaN(m.top)) m.top = 0.5;
            if (isNaN(m.bottom)) m.bottom = 0.5;
            if (isNaN(m.left)) m.left = 0.5;
            if (isNaN(m.right)) m.right = 0.5;

            let html = `<style>
                @page { size: ${pw}cm ${ph}cm; margin:0; }
                body { margin:0; padding:0; background:white; width:${pw}cm; min-height:${ph}cm; }
                .page-container { position:relative; width:${pw}cm; height:${ph}cm; overflow:hidden; page-break-after:always; }
                .img-wrap { position:absolute; box-sizing:border-box; }
                .img-content { width:100%; height:100%; display:flex; align-items:center; justify-content:center; position:relative; }
                .img-content img { width:100%; height:100%; object-fit:fill; }

                .crop-mark {
                    position: absolute;
                    width: ${panjang}mm;
                    height: ${panjang}mm;
                    pointer-events: none;
                    z-index: 25;
                    -webkit-print-color-adjust: exact !important;
                    print-color-adjust: exact !important;
                }
                .crop-mark.tl {
                    top: -${offset}mm;
                    left: -${offset}mm;
                    border-top: ${tebal}mm solid #000;
                    border-left: ${tebal}mm solid #000;
                }
                .crop-mark.tr {
                    top: -${offset}mm;
                    right: -${offset}mm;
                    border-top: ${tebal}mm solid #000;
                    border-right: ${tebal}mm solid #000;
                }
                .crop-mark.bl {
                    bottom: -${offset}mm;
                    left: -${offset}mm;
                    border-bottom: ${tebal}mm solid #000;
                    border-left: ${tebal}mm solid #000;
                }
                .crop-mark.br {
                    bottom: -${offset}mm;
                    right: -${offset}mm;
                    border-bottom: ${tebal}mm solid #000;
                    border-right: ${tebal}mm solid #000;
                }
            </style>`;

            let sheetsHtml = '';
            for (let q = 0; q < qty; q++) {
                let pageHtml = `<div class="page-container">`;
                canvasItems.forEach(item => {
                    let marksHtml = '';
                    if (useKres) {
                        marksHtml = `
                            <div class="crop-mark tl"></div>
                            <div class="crop-mark tr"></div>
                            <div class="crop-mark bl"></div>
                            <div class="crop-mark br"></div>
                        `;
                    }
                    // Geser koordinat gambar sesuai margin halaman cetak yang diinput
                    let itemXWithMargin = item.x + m.left;
                    let itemYWithMargin = item.y + m.top;
                    
                    pageHtml += `<div class="img-wrap" style="left:${itemXWithMargin}cm; top:${itemYWithMargin}cm; width:${item.renderW}cm; height:${item.renderH}cm;">
                                    <div class="img-content">
                                        <img src="${item.data}" style="width:${item.w}cm; height:${item.h}cm; transform:rotate(${item.rot}deg); object-fit:fill;">
                                        ${marksHtml}
                                    </div>
                                 </div>`;
                });
                pageHtml += '</div>';
                sheetsHtml += pageHtml;
            }

            let f = document.getElementById('p-frame');
            f.style.display = 'block';
            f.contentWindow.document.open();
            f.contentWindow.document.write(html + sheetsHtml);
            f.contentWindow.document.close();
            
            let btn = document.getElementById('btn-do-layout-print');
            btn.innerText = 'RENDERING...';
            btn.disabled = true;
            
            setTimeout(() => {
                f.contentWindow.print();
                f.style.display = 'none';
                btn.innerText = 'MULAI CETAK LAYOUT';
                btn.disabled = false;
                
                // Simpan hasil cetak ke dalam database log dengan label unik agar terpisah
                saveHistory({
                    inv: inv,
                    typeLabel: 'OP_LAYOUTER_PROD',
                    qty: qty,
                    cap: `Layouter 2D - Material: ${mat}`,
                    fileData: canvasItems[0] ? canvasItems[0].data : null,
                    isPdf: false,
                    partner: 'LAYOUTER'
                });

                playSound('done-sound');
                closeLayoutPrintModal();
                // Jangan tutup layouter otomatis agar user bisa melihat hasil
                // closeManualLayouter();  // Dikomentari agar layouter tetap terbuka
                showToast('🖨️ Cetak Layouter Berhasil!', 'success');
                
                // Render ulang canvas untuk memastikan tampilan tetap
                renderCanvasItems();
            }, 1000);
        }

        function toBase64(file) {
            return new Promise((resolve, reject) => {
                let reader = new FileReader();
                reader.onload = () => resolve(reader.result);
                reader.onerror = reject;
                reader.readAsDataURL(file);
            });
        }

        function downloadAsset(data, name) {
            let a = document.createElement('a');
            a.href = data;
            a.download = name;
            a.click();
        }

        function clearTimeline() {
            if (confirm('🗑️ Hapus seluruh timeline?')) {
                db.transaction('stream', 'readwrite').objectStore('stream').clear().onsuccess = () => {
                    streamCache = [];
                    renderStream(true);
                };
            }
        }

        // ---------- MANUAL LAYOUTER ----------
        function openManualLayouter() {
            if (manualSources.length === 0) {
                loadImagesFromManifest();
            }
            document.getElementById('modal-manual-layout').style.display = 'grid';
            // Pastikan canvas dirender dengan benar saat dibuka
            setTimeout(() => {
                updatePaperCanvas();
                renderCanvasItems();
            }, 50);
        }

        function closeManualLayouter() {
            document.getElementById('modal-manual-layout').style.display = 'none';
        }

        async function handleManualUpload(input) {
            for (let f of input.files) {
                let d = await toBase64(f);
                manualSources.push({ id: Date.now() + Math.random(), data: d, name: f.name });
            }
            renderManualSourceList();
            input.value = ''; // Mengosongkan value input agar berkas yang sama dapat diunggah berulang kali
        }

        function renderManualSourceList() {
            let list = document.getElementById('manual-source-list');
            list.innerHTML = '';
            if (!manualSources.length) {
                list.innerHTML = '<div style="grid-column:1/-1; padding:20px; text-align:center; opacity:0.3;">NO ASSETS</div>';
                return;
            }
            manualSources.forEach((s, idx) => {
                let card = document.createElement('div');
                card.className = 'asset-card';
                card.onclick = () => addToCanvas(s.id);
                card.innerHTML = `<div class="asset-thumb" style="height:60px; background:#f0f2f5; display:flex; align-items:center; justify-content:center; cursor:pointer;"><img src="${s.data}" style="max-height:100%; max-width:100%;"></div>
                                 <div class="asset-info" style="font-size:0.65rem; padding:4px; display:flex; justify-content:space-between; align-items:center;">
                                 <span class="asset-name" style="text-overflow:ellipsis; overflow:hidden; white-space:nowrap; max-width:60px;">${s.name}</span>
                                 <span class="asset-del" onclick="event.stopPropagation(); manualSources.splice(${idx},1); renderManualSourceList();" style="color:var(--danger); cursor:pointer;">🗑️</span></div>`;
                list.appendChild(card);
            });
        }

        // ---------- GALLERY FUNCTIONS ----------
        function renderGallery() {
            const container = document.getElementById('gallery-container');
            if (!container) return;
            if (galleryAssets.length === 0) {
                container.innerHTML = '<div style="grid-column:1/-1; text-align:center; padding:10px; color:var(--fb-text-dim);">Aset Kosong</div>';
                return;
            }
            let html = '';
            galleryAssets.forEach((asset, index) => {
                html += `
                    <div class="gallery-item" onclick="addGalleryImageToJob('${asset.url}', '${asset.name}')" 
                         style="cursor:pointer; border-radius:6px; overflow:hidden; border:1px solid var(--fb-border); background:#fff; transition:transform 0.15s; aspect-ratio:1/1; display:flex; align-items:center; justify-content:center; padding:4px;">
                        <img src="${asset.url}" style="max-width:100%; max-height:100%; object-fit:contain;" title="${asset.name}">
                    </div>
                `;
            });
            container.innerHTML = html;
        }

        function addGalleryImageToJob(imageUrl, fileName) {
            let targetIdx = activeJobIdx;
            if (targetIdx === null || targetIdx >= tempJobs.length) {
                addNewJob();
                targetIdx = tempJobs.length - 1;
            }
            const fakeFile = {
                data: imageUrl,
                thumb: imageUrl,
                isPdf: false,
                name: fileName
            };
            tempJobs[targetIdx].files.push(fakeFile);
            renderJobs();
            showToast(`🖼️ Aset ${fileName} ditambahkan ke baris aktif.`, 'success');
        }

        function refreshGallery() {
            loadImagesFromManifest();
            showToast('📂 Mengambil ulang daftar aset dari server...', 'info');
        }

        function updatePaperCanvas() {
            let p = document.getElementById('paper-canvas');
            let dim = document.getElementById('m-paper').value.split(',');
            let scale = 10;
            p.style.width = (dim[0] * scale) + 'px';
            p.style.minHeight = (dim[1] * scale) + 'px';
            p.style.height = 'auto';
            recalculateLayout();
            renderCanvasItems();
        }

        // ---------- LAYOUTER ENGINE: RECALCULATE LAYOUT WITH DELETION AUTOMATIC SHIFT ----------
        function recalculateLayout() {
            let paperDim = document.getElementById('m-paper').value.split(',');
            let pW = parseFloat(paperDim[0]);
            
            let gapEl = document.getElementById('l-gap');
            let gap = 0;
            if (gapEl && gapEl.value !== '') {
                gap = parseFloat(gapEl.value);
                if (isNaN(gap)) gap = 0;
            }

            let tempX = 0;
            let tempY = 0;
            let tempMaxRowH = 0;

            canvasItems.forEach(item => {
                // Pastikan renderW dan renderH memiliki nilai default jika tidak ada
                if (!item.renderW || isNaN(item.renderW)) item.renderW = item.w || 5;
                if (!item.renderH || isNaN(item.renderH)) item.renderH = item.h || 5;
                
                // Jika posisi horizontal melebihi batas lebar kertas, bungkus ke baris baru
                if (tempX + item.renderW > pW) {
                    tempX = 0;
                    tempY += tempMaxRowH + gap;
                    tempMaxRowH = 0;
                }
                item.x = tempX;
                item.y = tempY;

                tempX += item.renderW + gap;
                if (item.renderH > tempMaxRowH) {
                    tempMaxRowH = item.renderH;
                }
            });

            // Perbarui koordinat global penunjuk penulisan berikutnya
            currentX = tempX;
            currentY = tempY;
            maxRowH = tempMaxRowH;
        }

        // Fungsi addToCanvas sekarang menyimpan srcName untuk pencocokan saat reload
        function addToCanvas(srcId) {
            let src = manualSources.find(s => s.id === srcId);
            if (!src) {
                showToast('❌ Aset tidak ditemukan!', 'error');
                return;
            }
            let w = parseFloat(document.getElementById('m-w').value) || 5;
            let h = parseFloat(document.getElementById('m-h').value) || 5;
            let rot = 0;
            
            let renderW = w;
            let renderH = h;
            
            canvasItems.push({
                id: Date.now() + Math.random(),
                srcId: srcId,
                srcName: src.name, // Simpan nama file untuk pencocokan saat reload
                data: src.data,
                x: 0,
                y: 0,
                w, h, rot,
                renderW, renderH
            });
            
            recalculateLayout();
            renderCanvasItems();
            showToast(`✅ Aset "${src.name}" ditambahkan ke canvas`, 'success');
        }

        function renderCanvasItems() {
            let p = document.getElementById('paper-canvas');
            if (!p) return;
            let scale = 10;
            p.innerHTML = '';
            
            if (!canvasItems.length) {
                // Tampilkan pesan kosong
                let emptyMsg = document.createElement('div');
                emptyMsg.style.cssText = 'position:absolute; top:50%; left:50%; transform:translate(-50%,-50%); color:#999; font-size:0.9rem; text-align:center;';
                emptyMsg.innerText = '📭 Klik aset di samping untuk menambah ke canvas';
                p.appendChild(emptyMsg);
                return;
            }
            
            canvasItems.forEach((item, idx) => {
                let d = document.createElement('div');
                d.className = 'canvas-item';
                
                // Pastikan semua nilai numerik valid
                let xPos = (isNaN(item.x) ? 0 : item.x) * scale;
                let yPos = (isNaN(item.y) ? 0 : item.y) * scale;
                let widthVal = (isNaN(item.renderW) ? (item.w || 5) : item.renderW) * scale;
                let heightVal = (isNaN(item.renderH) ? (item.h || 5) : item.renderH) * scale;
                let imgW = (isNaN(item.w) ? 5 : item.w) * scale;
                let imgH = (isNaN(item.h) ? 5 : item.h) * scale;
                let rotVal = isNaN(item.rot) ? 0 : item.rot;
                
                d.style.left = xPos + 'px';
                d.style.top = yPos + 'px';
                d.style.width = widthVal + 'px';
                d.style.height = heightVal + 'px';
                d.innerHTML = `<div style="position:relative; width:100%; height:100%; display:flex; align-items:center; justify-content:center;">
                    <img src="${item.data || ''}" style="width:${imgW}px; height:${imgH}px; transform:rotate(${rotVal}deg); object-fit:fill;" 
                         onerror="this.style.display='none'; this.parentElement.innerHTML='<span style=\\'color:#999;font-size:0.6rem;\\'>⚠️ Gagal muat</span>'">
                    <div class="item-del" onclick="canvasItems.splice(${idx},1); recalculateLayout(); renderCanvasItems();">×</div>
                </div>`;
                p.appendChild(d);
            });
        }

        function clearManualCanvas() {
            canvasItems = [];
            currentX = 0; currentY = 0; maxRowH = 0;
            renderCanvasItems();
            showToast('🗑️ Canvas telah dibersihkan', 'info');
        }

        // ---------- RELOAD LAYOUTER (FUNGSI BARU) ----------
        function reloadLayouter() {
            // Animasi tombol reload
            const btn = document.getElementById('btn-reload-layouter');
            if (btn) {
                btn.classList.add('spin');
                setTimeout(() => btn.classList.remove('spin'), 600);
            }
            
            // Simpan data canvas saat ini sebelum reload
            const savedItems = JSON.parse(JSON.stringify(canvasItems));
            
            // Muat ulang aset dari manifest
            loadImagesFromManifest().then(() => {
                // Kembalikan item canvas yang tersimpan dengan mencocokkan berdasarkan nama file
                canvasItems = [];
                savedItems.forEach(saved => {
                    // Cari sumber berdasarkan srcName (nama file) terlebih dahulu
                    let found = manualSources.find(s => s.name === saved.srcName);
                    if (!found) {
                        // Jika tidak ditemukan, coba cari berdasarkan srcId (fallback)
                        found = manualSources.find(s => s.id === saved.srcId);
                    }
                    if (found) {
                        canvasItems.push({
                            ...saved,
                            srcId: found.id, // perbarui dengan ID baru
                            data: found.data
                        });
                    } else {
                        // Jika benar-benar hilang, skip
                        showToast(`⚠️ Aset "${saved.srcName || saved.srcId}" tidak ditemukan, dilewati`, 'info');
                    }
                });
                
                // Render ulang canvas
                recalculateLayout();
                renderCanvasItems();
                renderManualSourceList();
                renderGallery();
                showToast('🔄 Layouter berhasil dimuat ulang!', 'success');
            }).catch(() => {
                // Fallback: reload manual
                loadImagesFromManifest();
                // Tetap pertahankan item yang ada dengan data yang sudah ada (jika masih tersimpan)
                canvasItems = savedItems;
                recalculateLayout();
                renderCanvasItems();
                renderManualSourceList();
                renderGallery();
                showToast('🔄 Layouter dimuat ulang (fallback)', 'success');
            });
        }

        async function loadImagesFromManifest() {
            try {
                const fileNames = [
                    "VW.jpg", "UNICORN.jpg", "TRAVELING.jpg", "SWEAT-CAT.jpg", "SUCCES.jpg",
                    "SAMURAI.jpg", "PANTAI.jpg", "ONE-PICE.jpg", "OCEANS.jpg", "NOTHINK.jpg",
                    "MOTOR.jpg", "MOOD-PANDA.jpg", "MEOW.jpg", "LOVE.jpg", "KUCING LUTCU.jpg",
                    "ITSOK.jpg", "INDONESIA.jpg", "IDEAS=COFFEE.jpg", "GAME.jpg", "AESTETIC.jpg",
                    "ASTRONOT.jpg", "AVATAR.jpg", "BE-POSITIVE.jpg", "BEACH.jpg", "BT21.jpg",
                    "COFFEE.jpg", "DORAEMON.jpg", "FARM.jpg", "FLOWER-NATURE.jpg", "H013.jpg",
                    "H014.jpg", "H015.jpg", "H016.jpg", "H017.jpg", "H018.jpg", "H019.jpg",
                    "H020.jpg", "H021.jpg", "H022.jpg", "H023.jpg", "a.png", "2.png",
                    "5.png", "1.png", "4.png"
                ];

                manualSources = [];
                galleryAssets = [];
                
                fileNames.forEach(fileName => {
                    const imageUrl = `img/${fileName}`;
                    manualSources.push({ id: Date.now() + Math.random(), data: imageUrl, name: fileName });
                    galleryAssets.push({ id: Date.now() + Math.random(), url: imageUrl, name: fileName });
                });

                renderManualSourceList();
                renderGallery();
            } catch (error) {
                console.warn('Gagal memuat galeri:', error);
            }
        }

        reinitializeLoginListeners();
        window.addEventListener('online', () => {
            if (localStorage.getItem('kts_mode') === 'cloud' && peer) peer.reconnect?.();
        });
        window.addEventListener('offline', () => alert('⚠️ Jaringan internet putus. Silakan alihkan ke mode LAN LOKAL.'));
        
        window.addEventListener('dragover', e => e.preventDefault());
        window.addEventListener('drop', e => e.preventDefault());

        // ---------- FITUR CHAT PRIBADI INLINE ----------
        let activeChatPartner = null;
        let chatHistory = {};
        let unreadChats = {};

        function toggleInlineChat(partnerId) {
            if (activeChatPartner === partnerId) {
                activeChatPartner = null;
            } else {
                activeChatPartner = partnerId;
                unreadChats[partnerId] = 0;
            }
            updatePeerUI();
        }

        function sendInlineChatMessage(partnerId) {
            let input = document.getElementById(`chat-input-${partnerId}`);
            if (!input) return;
            let text = input.value.trim();
            if (!text) return;

            let conn = activeConns.find(c => c.peer === partnerId);
            if (!conn) {
                alert("❌ Pengiriman gagal. Node tujuan offline.");
                return;
            }

            let msg = {
                type: 'chat',
                sender: myId,
                text: text,
                time: new Date().toLocaleTimeString('id-ID', { hour: '2-digit', minute: '2-digit' })
            };

            conn.send(msg);

            if (!chatHistory[partnerId]) chatHistory[partnerId] = [];
            chatHistory[partnerId].push(msg);

            input.value = '';
            renderInlineChatMessages(partnerId);
        }

        function handleIncomingChat(data, from) {
            if (!chatHistory[from]) chatHistory[from] = [];
            chatHistory[from].push(data);

            playSound('notif-sound'); 

            if (activeChatPartner === from) {
                renderInlineChatMessages(from);
            } else {
                unreadChats[from] = (unreadChats[from] || 0) + 1;
                showToast(`💬 Pesan masuk dari ${from}`, 'info');
                updatePeerUI();
            }
        }

        function renderInlineChatMessages(partnerId) {
            let container = document.getElementById(`chat-messages-${partnerId}`);
            if (!container) return;
            container.innerHTML = '';

            if (!chatHistory[partnerId] || chatHistory[partnerId].length === 0) {
                container.innerHTML = '<div style="text-align:center; padding:10px; color:var(--fb-text-dim); font-size:0.7rem; margin: auto 0;">Kirim pesan...</div>';
                return;
            }

            chatHistory[partnerId].forEach(m => {
                let isMe = m.sender === myId;
                let wrapper = document.createElement('div');
                wrapper.style.display = 'flex';
                wrapper.style.flexDirection = 'column';
                wrapper.style.alignSelf = isMe ? 'flex-end' : 'flex-start';
                wrapper.style.maxWidth = '85%';

                let bubble = document.createElement('div');
                bubble.style.padding = '6px 10px';
                bubble.style.borderRadius = '14px';
                bubble.style.fontSize = '0.75rem';
                bubble.style.wordBreak = 'break-word';

                if (isMe) {
                    bubble.style.background = 'var(--fb-blue)';
                    bubble.style.color = '#fff';
                    bubble.style.borderRadius = '12px 12px 0px 12px';
                } else {
                    bubble.style.background = '#e4e6eb';
                    bubble.style.color = 'var(--fb-text)';
                    bubble.style.borderRadius = '12px 12px 12px 0px';
                }
                bubble.innerText = m.text;

                let timeSpan = document.createElement('span');
                timeSpan.style.fontSize = '0.6rem';
                timeSpan.style.color = 'var(--fb-text-dim)';
                timeSpan.style.marginTop = '2px';
                timeSpan.style.alignSelf = isMe ? 'flex-end' : 'flex-start';
                timeSpan.innerText = m.time;

                wrapper.appendChild(bubble);
                wrapper.appendChild(timeSpan);
                container.appendChild(wrapper);
            });

            container.scrollTop = container.scrollHeight;
        }
    </script>
</body>
</html>
