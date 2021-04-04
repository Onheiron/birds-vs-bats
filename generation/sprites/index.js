var bmp = require("bmp-js");
var fs = require("fs");

Array.prototype.flatten = function () {
  return this.reduce((pre, curr) => pre.concat(curr), []);
};

function tileImage(path, startingTile) {
  var bmpBuffer = fs.readFileSync(path);
  var bmpData = bmp.decode(bmpBuffer);

  const bytes = [];
  let currentShift = 6;
  let currentByte = 0x00;
  for (let i = 0; i < bmpData.data.length; i += 4) {
    let level = 0;
    if (bmpData.data[i + 1] == 0xff) level = 0;
    else if (bmpData.data[i + 1] == 0xeb) level = 1;
    else if (bmpData.data[i + 1] == 0xa9) level = 2;
    else if (bmpData.data[i + 1] == 0x00) level = 3;
    currentByte = currentByte | ((level & 0x03) << currentShift);
    currentShift -= 2;
    if (currentShift < 0) {
      currentShift = 6;
      bytes.push(currentByte);
      currentByte = 0x00;
    }
  }
  console.log("BYTES", bytes.length);
  const tiles = {};
  const tilemap = [];
  for (let i = 0; i < bytes.length; i += 16) {
    const key = JSON.stringify(bytes.slice(i, i + 16));
    if (!tiles[key]) {
      tiles[key] = startingTile;
      startingTile += 1;
    }
    tilemap.push(tiles[key]);
  }
  console.log(
    JSON.stringify(
      Object.keys(tiles)
        .map(key => JSON.parse(key))
        .flatten()
        .map((val) => "0x" + val.toString(16).padStart(2, "0"))
    )
      .replace("[", "{")
      .replace("]", "}")
      .replace(/\"/g, "")
  );

  console.log(
    JSON.stringify(
      Object.values(tiles).map(
        (val) => "0x" + val.toString(16).padStart(2, "0")
      )
    )
      .replace("[", "{")
      .replace("]", "}")
      .replace(/\"/g, "")
  );

  console.log(
    JSON.stringify(
      tilemap.map((val) => "0x" + val.toString(16).padStart(2, "0"))
    )
      .replace("[", "{")
      .replace("]", "}")
      .replace(/\"/g, "")
  );
}

tileImage("./files/ui.bmp", 0x00);