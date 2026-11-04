<p align="center">
  <img src="https://raw.githubusercontent.com/h1z1z1h16584/ps5-y2jb-autoloader/main/src/icon0.png" width="128" alt="PS5 Y2JB Autoloader Logo" />
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
  <img src="https://raw.githubusercontent.com/h1z1z1h16584/ps5-y2jb-autoloader/main/y2jb_screenshot.png" width="600" alt="PS5 Y2JB Autoloader Screenshot" />
</p>

## How to Use

There are two primary ways to run payloads using the autoloader:

#### 🟢 Option 1: Payload Manager

If no `autoload.txt` configuration is detected, the autoloader automatically starts **Payload Manager** — a fully featured PS5 payload manager equipped with a web UI.

Launch payloads and manage files directly through your web browser without manual configuration files or FTP transfers beforehand.

Simply run the autoloader; if no custom config exists, Payload Manager will handle the rest.

> [!NOTE]
> Payload Manager includes its own built-in autoload feature configured via its web UI, which is independent of the file-based `autoload.txt` system outlined below.

#### ⚙️ Option 2: Manual Config (`autoload.txt`)

For a direct, headless, and chained execution sequence:

1.  Create a directory named `ps5_autoloader`.
2.  Inside `ps5_autoloader`, place your `.elf` or `.bin` files alongside an `autoload.txt` file.
    *   List payloads line-by-line (e.g., `etaHEN.elf`).
    *   File names are case-sensitive.
    *   Use `!<milliseconds>` for timed delays (e.g., `!1000` delays execution by 1000 ms).
3.  Place the `ps5_autoloader` directory in one of the following locations (checked in order of priority):
    *   Root of a USB drive (Highest Priority)
    *   Internal storage: `/data/ps5_autoloader`

> [!TIP]
> If an `autoload.txt` file is present, Payload Manager will not launch automatically. To make Payload Manager available alongside automated payloads, place `pldmgr.elf` inside your `ps5_autoloader` folder and add it to `autoload.txt`.

## How to Update

To update the autoloader:

1.  Download `y2jb_update.zip` from the [Releases page](https://github.com/h1z1z1h16584/ps5-y2jb-autoloader/releases).
2.  Copy `y2jb_update.zip` to the root of an exFAT/FAT32 formatted USB drive.
3.  Plug the drive into the PS5 and start the YouTube app. The autoloader will detect and install the update automatically.

## Setup Instructions

> [!IMPORTANT]
> **Relapse Network Requirement:**
>
> Relapse requires an active network interface (Wi-Fi or Ethernet connected to a local router; internet connectivity is not required).
>
> *   **FW 7.00 – 10.01:** Relapse is selected if a network connection is detected (falls back to Lapse otherwise).
> *   **FW 10.20 – 13.60:** An active network interface is strictly required.

### Jailbroken PS5 (WebKit, Lua, BD-JB)

#### 1. Install Matching YouTube Version

Install the YouTube app version that corresponds to your console's firmware:

| Firmware Range  | YouTube Title IDs                 | Required App Version |
| --------------- | --------------------------------- | -------------------- |
| 4.03 – 12.40    | PPSA01650 / PPSA01651 / PPSA01652 | v01.000.003          |
| 12.60 – 13.20   | PPSA01650 / PPSA01651 / PPSA01652 | v01.000.030          |
| 13.40 – 13.60   | PPSA01650 / PPSA01651 / PPSA01652 | v01.009.253          |

#### 2. Deploy Image to PS5

Releases provide both `download0.dat` (raw UFS2 image, ~321 MB) and `download0.dat.zip` (~1–2 MB). The PS5 requires the uncompressed raw image to be present on its internal storage.

##### Default (Recommended): USB Installer Payload

The standalone payload (usb-y2jb-installer.elf) installs the image offline from a USB drive directly to the YouTube directory (`/user/download/PPSA0165*`). It automatically unzips the payload on the console if you use the `.zip` archive.

1.  Format a USB drive as FAT32 or exFAT.
2.  Place either `download0.dat.zip` or `download0.dat` on the root of your USB drive. (The compressed `.zip` is prioritized for faster transfer).
3.  Insert the USB drive into your PS5.
4.  Send the installer ELF to your PS5's payload listener (port 9021):
    ```sh
    nc -w 3 <PS5_IP> 9021 < build/usb-y2jb-installer.elf
    ```

##### Manual Alternative: Deploy via FTP

If you prefer deploying manually, transfer the uncompressed image over FTP:

1.  Extract the raw image if using the zip archive:
    ```sh
    unzip download0.dat.zip
    ```
2.  Connect to the PS5 via FTP and upload `download0.dat` to your YouTube title directory (e.g., `/user/download/PPSA0165*/`).


## Building the USB Payload

To build the `usb-y2jb-installer.elf` binary from source, you must have the [ps5-payload-sdk](https://github.com/ps5-payload-dev/sdk) installed.

```sh
./build_usb_payload.sh
```

## Additional Information & FAQ

<details>
<summary><b>How do I use different autoload configurations for multiple YouTube apps?</b></summary>
<br>

If you have multiple regional YouTube apps installed, you can create app-specific autoloader directories. Name your directory `ps5_autoloader_[TITLE_ID]` (e.g., `ps5_autoloader_PPSA01650`). This allows you to maintain distinct `autoload.txt` configurations for each app. App-specific directories always take precedence over the generic `ps5_autoloader` directory.

Example structure on a USB drive:
```
USB Root
├── ps5_autoloader_PPSA01650/
│   └── autoload.txt
├── ps5_autoloader_PPSA01651/
│   └── autoload.txt
└── ps5_autoloader/
    └── autoload.txt          (generic fallback)
```
</details>

<details>
<summary><b>How can I use a custom ELF Loader version?</b></summary>
<br>

By default, the autoloader uses an embedded ELF loader that only accepts connections from the PS5 itself (localhost). This improves security by preventing unauthorized devices on your network from sending payloads to your console.

If you need an ELF Loader that listens for payloads from external devices:
1.  Place your custom ELF Loader (e.g., `elfldr.elf`) in your `ps5_autoloader` directory.
2.  Add `elfldr.elf` to your `autoload.txt`.
3.  If chaining other payloads directly after, add a delay (e.g., `!4000` for 4 seconds) to ensure the loader initializes its network socket before the next payload is sent.

Example `autoload.txt`:
```
# 1. Start custom ELF Loader
elfldr.elf

# 2. Wait 4 seconds for the listener to initialize
!4000

# 3. Load a subsequent payload
etaHEN.elf
```
</details>

## Credits

*   **Gezine** – Creator of the original Y2JB
*   **shahrilnet, null\_ptr** – Referenced code from Remote Lua Loader
*   **BenNoxXD** – ClosePlayer reference
*   **ntfargo** – V8 CVEs and CTF writeups
*   **abc and the psfree team** – Lapse implementation
*   **matem6** – P2JB implementation
*   **edisnord, notmaj0r** – Relapse implementations
*   **flat\_z, LM** – GPU RW using direct ioctl
*   **john-tornblom, EchoStretch** – Providing elfldr.elf payload
*   **hammer-83** – BD-J PS5 exploit references
*   **zecoxao, idlesauce, TheFlow** – Troubleshooting dlsym
*   **Dr.Yenyen and the PS5 R&D community** – Testing Y2JB
*   **Rush** – Creating Y2JB backup file
*   **Feyzee61** – `download0.dat` generator workflow
*   **ufm42** – `kexp` post-jailbreak all-in-one shellcode

## License

All unique additions and modifications in this fork are licensed under the **GNU General Public License v3.0 (GPL-3.0)**.
The original Y2JB base code remains under its original **MIT License** (see `LICENSE-MIT`).

## Disclaimer

This tool is provided for research and development purposes only. Use at your own risk. The developers are not responsible for any damage, data loss, or other consequences resulting from the use of this software.
