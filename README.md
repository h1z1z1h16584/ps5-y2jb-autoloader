<p align="center">
 <img src="./src/icon0.png" width="128" />
</p>
<h1 align="center">PS5 Y2JB Autoloader</h1>
<h3 align="center">Fork of <a href="https://github.com/Gezine/Y2JB">Y2JB</a></h3>
&nbsp;
<p align="center">Automatically loads the kernel exploit and your elf payloads.<br>Supports PS5 firmwares 4.03-13.60</p>

<p align="center">
    <b>Other Autoloaders:</b><br>
    <a href="https://github.com/itsPLK/ps5-webkit-autoloader">WebKit</a> | 
    <a href="https://github.com/itsPLK/ps5-bdjb-autoloader">BD-JB</a> | 
    <a href="https://github.com/itsPLK/ps5-lua-autoloader">Lua</a>
</p>

<p align="center">
 <img src="./y2jb_screenshot.png" width="600" />
</p>

## How to Use

There are two ways to use the autoloader:

### 🟢 Option 1: Payload Manager

If no `autoload.txt` config is found, the autoloader will automatically launch **[Payload Manager](https://github.com/itsPLK/ps5-payload-manager)** — a fully-featured PS5 payload manager with a web UI. This lets you configure and send payloads directly from your browser, without needing to manually set up config files or transfer ELF files ahead of time.

Just run the autoloader — if there's nothing configured, Payload Manager starts automatically.

> **Note:** Payload Manager also has its own built-in autoload feature, which lets you configure payloads to load automatically on startup — all managed through its web UI. This is separate from the `autoload.txt` mechanism described below.

---

### ⚙️ Option 2: Manual Config (`autoload.txt`)

For a fixed, automated payload chain, you can configure payloads manually:

- Create a directory named `ps5_autoloader`.
- Inside this directory, place your `.elf` / `.bin` files, and an `autoload.txt` file.
  - In `autoload.txt`, list the files you want to load, one filename per line.
  - Filenames are case-sensitive — ensure each name exactly matches the file.
  - You can add lines like `!1000` to make the loader wait 1000 ms before sending the next payload.
- Put the `ps5_autoloader` directory in one of these locations (priority order - highest first):
  - Root of a USB drive
  - Internal drive: `/data/ps5_autoloader`

> **Note:** When an `autoload.txt` config is found, Payload Manager is **not** launched automatically. If you also want Payload Manager available, place `pldmgr.elf` in your `ps5_autoloader` directory and add it to `autoload.txt`.

## How to Update

You can update the autoloader by simply placing **`y2jb_update.zip`** (from the [Releases page](https://github.com/itsPLK/ps5_y2jb_autoloader/releases)) on the **root** of a USB drive, and starting the app.

```bash
# Place y2jb_update.zip on the root of a USB drive, then start YouTube on the PS5.
# The autoloader will detect and apply the update automatically.
```
##Setup Instructions
Installation is the same as the original Y2JB (remote loader).

Jailbroken PS5 (Webkit, Lua, BD-JB)
Install YouTube (PPSA01650 / PPSA01651 / PPSA01652):

Firmware	YouTube Version
4.03 – 12.40	v01.000.003
12.60 – 13.20	v01.000.030
13.40 – 13.60	v01.009.253
Then FTP download0.dat from Releases to /user/download/PPSA0165*/.

bash
# Example: FTP the raw image to the YouTube title directory
ftp <PS5_IP>
# then:
# put download0.dat /user/download/PPSA01650/download0.dat
Note: Releases ship both download0.dat (raw UFS2 image, ~321MB) and download0.dat.zip (~1-2MB). If you download the .zip, extract it first to get the raw download0.dat — the PS5 needs the uncompressed image. Alternatively, use the USB Installer payload below, which extracts the .zip directly on the console.

bash
# If you downloaded download0.dat.zip, extract before FTP:
unzip download0.dat.zip
# -> produces download0.dat, then FTP it as shown above
Non-Jailbroken PS5
You might find a system backup with pre-configured Autoloader (I don't distribute such backups).

You can also restore Y2JB (remote loader) system backup, and then:

bash
# Option A: FTP download0.dat into the default title directory
ftp <PS5_IP>
# put download0.dat /user/download/PPSA01650/download0.dat

# Option B: install a YouTube app from another region and FTP there instead
# put download0.dat /user/download/PPSA0165*/download0.dat
[!NOTE]
Relapse requires an active network interface (Wi-Fi or Ethernet connected to a local network; Internet access is not required). On FW 7.00–10.01, it is used when a network interface is detected (falling back to Lapse otherwise). On FW 10.20–13.60, an active network interface is required.

USB Installer Payload
A standalone payload is included to install download0.dat offline from an inserted USB drive directly to the YouTube directory on the console (/user/download/PPSA0165*).

Building the Payload
Requires ps5-payload-sdk.

bash
./build_usb_payload.sh
Usage
bash
# 1. Format a USB drive as exFAT or FAT32.

# 2. Place EITHER download0.dat.zip OR download0.dat on the root of the USB drive.
#    If both are present, the .zip is preferred (smaller transfer, streamed extraction).
#    The payload extracts/copies the image directly to /user/download/PPSA0165*/download0.dat.

# 3. Insert the USB drive into your PS5.

# 4. Send the installer ELF to port 9021 on the console:
nc -w 3 <PS5_IP> 9021 < build/usb-y2jb-installer.elf
Additional Info
<Details> <Summary><i>How to have different autoload configs for multiple YT apps?</i></Summary>
If you want to use multiple YT apps from different regions, name your directory ps5_autoloader_[TITLE_ID], e.g. ps5_autoloader_PPSA01650. This allows you to have different autoload.txt files for each app (these directories always take precedence over the generic ps5_autoloader directory).

bash
# Example layout on USB root:
# /ps5_autoloader_PPSA01650/autoload.txt
# /ps5_autoloader_PPSA01651/autoload.txt
# /ps5_autoloader/autoload.txt   (generic fallback)
</Details><Details> <Summary><i>How to use custom ELF Loader version?</i></Summary>
By default, the autoloader uses a custom version of elfldr that only accepts connections from the PS5 itself (localhost). This improves security by preventing other devices on your network from sending payloads to your console.

If you want to use a "normal" ELF Loader that allows sending payloads from any device:

bash
# 1. Place your custom ELF Loader (e.g. elfldr.elf) in the ps5_autoloader directory.

# 2. Add elfldr.elf to your autoload.txt.

# 3. If you are loading other payloads right after elfldr.elf in autoload.txt,
#    add a sleep command immediately after it (like !4000 for 4 seconds)
#    to give the new ELF Loader time to start up and listen before
#    subsequent payloads are sent.

# Example autoload.txt:
# --------------------
# # Load custom ELF Loader
# elfldr.elf
# # Give it 4 seconds to start up (only needed if sending more payloads)
# !4000
# # Send other payloads
# etaHEN.elf
</Details>
Credits
Gezine - creator of the original Y2JB

shahrilnet, null_ptr - Referenced many codes from Remote Lua Loader

BenNoxXD - ClosePlayer reference

ntfargo - Thanks for providing V8 CVEs and CTF writeups

abc and psfree team - Lapse implementation

matem6 - P2JB implementation

edisnord , notmaj0r - Relapse implementations

flat_z and LM - Helping implement GPU rw using direct ioctl

john-tornblom and EchoStretch - Providing elfldr.elf payload

hammer-83 - Various BD-J PS5 exploit references

zecoxao, idlesauce, and TheFlow - Helping troubleshoot dlsym

Dr.Yenyen and PS5 R&D community - Testing Y2JB

Rush - Creating Y2JB backup file

Feyzee61 - download0.dat generator workflow

ufm42 - kexp used for PS5 post JB all-in-one shellcode

License
This project is licensed under the GPL-3.0 License.

The original Y2JB base code remains under its original MIT License (see LICENSE-MIT).
All unique modifications and additions in this fork are licensed under GPL-3.0.

Disclaimer
This tool is provided as-is for research and development purposes only. Use at your own risk. The developers are not responsible for any damage, data loss, or consequences resulting from the use of this software.
