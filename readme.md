<p align="center">
  <img src="./src/icon0.png" width="128" alt="PS5 Y2JB Autoloader Logo" />
</p>

<h1 align="center">PS5 Y2JB Autoloader</h1>
<h3 align="center">Fork of <a href="https://github.com/Gezine/Y2JB">Y2JB</a></h3>

<p align="center">
  Automatically loads the kernel exploit and your ELF payloads.<br>
  Supports PS5 firmwares <b>4.03 – 13.60</b>
</p>

<p align="center">
  <b>Other Autoloaders:</b><br>
  <a href="https://github.com/itsPLK/ps5-webkit-autoloader">WebKit</a> | 
  <a href="https://github.com/itsPLK/ps5-bdjb-autoloader">BD-JB</a> | 
  <a href="https://github.com/itsPLK/ps5-lua-autoloader">Lua</a>
</p>

<p align="center">
  <img src="./y2jb_screenshot.png" width="600" alt="PS5 Y2JB Autoloader Screenshot" />
</p>


Table of Contents
How to Use
Option 1: Payload Manager
Option 2: Manual Config (autoload.txt)
How to Update
Setup Instructions
Jailbroken PS5
1. Install Matching YouTube Version
2. Deploy Image to PS5
Default (Recommended): USB Installer Payload
Manual Alternative: Deploy via FTP
Non-Jailbroken PS5
Building the USB Payload
Additional Information & FAQ
Credits
License
Disclaimer

How to Use
There are two primary ways to run payloads using the autoloader:
🟢 Option 1: Payload Manager
If no autoload.txt configuration is detected, the autoloader automatically starts Payload Manager — a fully featured PS5 payload manager equipped with a web UI.
Launch payloads and manage files directly through your web browser without manual configuration files or manual FTP transfers beforehand.
Simply run the autoloader; if no custom config exists, Payload Manager will handle the rest.
[!NOTE]
Payload Manager includes its own built-in autoload feature configured via its web UI, independent of the file-based autoload.txt system outlined below.

⚙️ Option 2: Manual Config (autoload.txt)
For a direct, headless, and chained execution sequence:
Create a directory named ps5_autoloader.
Inside ps5_autoloader, place your .elf / .bin files alongside an autoload.txt file.
List payloads line-by-line (e.g., etaHEN.elf).
File names are case-sensitive.
Use !<milliseconds> for timed delays (e.g., !1000 delays execution by 1000 ms).
Place the ps5_autoloader directory in one of the following locations (checked in order of priority):
Root of a USB drive (Highest Priority)
Internal storage: /data/ps5_autoloader
[!TIP]
If an autoload.txt file is present, Payload Manager will not launch automatically. If you still want Payload Manager available alongside automated payloads, place pldmgr.elf inside your ps5_autoloader folder and add it to autoload.txt.

How to Update
To update the autoloader:
Download y2jb_update.zip from the Releases page.
Copy y2jb_update.zip to the root of an exFAT/FAT32 formatted USB drive.
Plug the drive into the PS5 and start YouTube. The autoloader will detect and install the update automatically.

Setup Instructions
[!IMPORTANT]
Relapse Network Requirement:
Relapse requires an active network interface (Wi-Fi or Ethernet connected to a local router; internet connectivity is not required).
FW 7.00 – 10.01: Relapse is selected if a network connection is detected (falls back to Lapse otherwise).
FW 10.20 – 13.60: An active network interface is strictly required.
Jailbroken PS5 (WebKit, Lua, BD-JB)
1. Install Matching YouTube Version
Install the YouTube app matching your current firmware version:
Firmware Range
YouTube Title IDs
Required App Version
4.03 – 12.40
PPSA01650 / PPSA01651 / PPSA01652
v01.000.003
12.60 – 13.20
PPSA01650 / PPSA01651 / PPSA01652
v01.000.030
13.40 – 13.60
PPSA01650 / PPSA01651 / PPSA01652
v01.009.253

2. Deploy Image to PS5
Releases provide both download0.dat (raw UFS2 image, ~321 MB) and download0.dat.zip (~1–2 MB). The PS5 requires the uncompressed raw image.
Default (Recommended): USB Installer Payload
The standalone payload installs the image offline from a USB drive directly to the YouTube directory (/user/download/PPSA0165*) and automatically unzips the payload on the console.
Format a USB drive as FAT32 or exFAT.
Place either download0.dat.zip or download0.dat on the root of your USB drive.
(If both are present, the compressed .zip is prioritized for faster transfer and stream extraction).
Insert the USB drive into your PS5.
Send the installer ELF to port 9021:
nc -w 3 <PS5_IP> 9021 < build/usb-y2jb-installer.elf
Manual Alternative: Deploy via FTP
If you prefer deploying manually without the USB installer payload, transfer the uncompressed image over FTP:
Extract the raw image if using the zip archive:
unzip download0.dat.zip
Connect to the PS5 via FTP and upload download0.dat to your YouTube title directory:
ftp <PS5_IP>
# Inside FTP prompt:
put download0.dat /user/download/PPSA01650/download0.dat

Non-Jailbroken PS5
If your console is not jailbroken:
Restore a system backup pre-configured with Y2JB / Autoloader. (Note: System backups are not distributed in this repository).
After restoring:
Option A: FTP download0.dat to /user/download/PPSA01650/download0.dat.
Option B: Install YouTube from another supported region and FTP download0.dat to that respective directory (/user/download/PPSA0165*/download0.dat).

Building the USB Payload
If you want to build the USB installer binary from source, this requires ps5-payload-sdk:
./build_usb_payload.sh

Additional Information & FAQ
<details>
<summary><b>How to use different autoload configs for multiple YouTube apps?</b></summary>
<br>

If you want to use multiple YouTube apps across different regions, name your directory ps5_autoloader_[TITLE_ID] (for example, ps5_autoloader_PPSA01650). This allows you to have distinct autoload.txt configurations for each app. App-specific directories always take precedence over the generic ps5_autoloader directory.
USB Root
├── ps5_autoloader_PPSA01650/
│   └── autoload.txt
├── ps5_autoloader_PPSA01651/
│   └── autoload.txt
└── ps5_autoloader/
    └── autoload.txt          (generic fallback)
</details>

<details>
<summary><b>How to use a custom ELF Loader version?</b></summary>
<br>

By default, the autoloader uses an embedded elfldr that only accepts connections from the PS5 itself (localhost). This improves security by preventing unauthorized devices on your network from sending payloads to your console.
If you want to use an ELF Loader that allows listening for payloads sent from external devices:
Place your custom ELF Loader (e.g., elfldr.elf) in your ps5_autoloader directory.
Add elfldr.elf to your autoload.txt.
If chaining payloads directly after elfldr.elf, add a sleep command (e.g., !4000 for 4 seconds) to ensure the loader finishes binding to the network socket before subsequent payloads are sent.
# Example autoload.txt:
# --------------------
# 1. Start custom ELF Loader
elfldr.elf

# 2. Wait 4 seconds for listener initialization
!4000

# 3. Load subsequent payload
etaHEN.elf
</details>


Credits
Gezine – Creator of the original Y2JB
shahrilnet, null_ptr – Referenced code from Remote Lua Loader
BenNoxXD – ClosePlayer reference
ntfargo – V8 CVEs and CTF writeups
abc and the psfree team – Lapse implementation
matem6 – P2JB implementation
edisnord, notmaj0r – Relapse implementations
flat_z, LM – GPU RW using direct ioctl
john-tornblom, EchoStretch – Providing elfldr.elf payload
hammer-83 – BD-J PS5 exploit references
zecoxao, idlesauce, TheFlow – Troubleshooting dlsym
Dr.Yenyen and the PS5 R&D community – Testing Y2JB
Rush – Creating Y2JB backup file
Feyzee61 – download0.dat generator workflow
ufm42 – kexp post-jailbreak all-in-one shellcode

License
All unique additions and modifications in this fork are licensed under the GNU General Public License v3.0 (GPL-3.0).
The original Y2JB base code remains under its original MIT License (see LICENSE-MIT).

Disclaimer
This tool is provided for research and development purposes only. Use at your own risk. The developers are not responsible for any damage, data loss, or consequences resulting from the use of this software.
