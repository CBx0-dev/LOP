const { execSync } = require("child_process");
const fs = require("fs");
const path = require("path");
const https = require("https");

function getLatestTag() {
    try {
        return execSync("git describe --tags --abbrev=0", {
            encoding: "utf8",
            stdio: ["ignore", "pipe", "ignore"],
        }).trim();
    } catch (err) {
        console.error("Failed to get latest git tag");
        process.exit(1);
    }
}

function getFilePostfix() {
  switch (process.platform) {
    case "win32":
      return "windows.exe";
    case "linux":
      return "linux";
    default:
      console.error(`Unsupported platform: ${process.platform}`);
      process.exit(1);
  }
}

function downloadFile(url, outputPath) {
    return new Promise((resolve, reject) => {
        fs.mkdirSync(path.dirname(outputPath), { recursive: true });

        const file = fs.createWriteStream(outputPath);
        function request(url) {
            https.get(url, (response) => {
                if (response.statusCode >= 300 && response.statusCode < 400 && response.headers.location) {
                    return request(response.headers.location);
                }

                if (response.statusCode !== 200) {
                    reject(new Error(`Download failed: ${response.statusCode} ${response.statusMessage}`));
                    return;
                }

                response.pipe(file);

                file.on("finish", () => {
                    file.close(resolve);
                });
            }).on("error", (err) => {
                fs.unlink(outputPath, () => reject(err));
            });
        }

        request(url);
    });
}

(async function () {
    const tag = getLatestTag();
    const postfix = getFilePostfix();

    const fileName = process.platform === "win32" ? "lopc.exe" : "lopc";
    const downloadUrl = `https://github.com/CBx0-dev/LOP/releases/download/${tag}/lopc-${postfix}`;

    const outputDir = path.join(__dirname, "..", "compiler", "snapshot");
    const cachePath = path.join(outputDir, "snapshot");
    const executablePath = path.join(outputDir, fileName);

    console.log(`Latest tag: ${tag}`);
    console.log(`Download URL: ${downloadUrl}`);

    if (fs.existsSync(cachePath)) {
        const cache = fs.readFileSync(cachePath, "utf-8");
        if (cache == tag) {
            console.log(`Required snapshot already present.`);
            return;
        }
    }

    fs.writeFileSync(cachePath, tag);

    try {
        await downloadFile(downloadUrl, executablePath);

        if (process.platform !== "win32") {
        fs.chmodSync(executablePath, 0o755);
        }

        console.log(`File saved to ${executablePath}`);
    } catch (err) {
        console.error("Download failed:", err.message);
        process.exit(1);
    }
})();

