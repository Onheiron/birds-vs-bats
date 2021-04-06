const readline = require("readline");
const fs = require("fs");

const levels = [];
let currentLevel;
let lineIndex = 0;

const readInterface = readline.createInterface({
  input: fs.createReadStream("./level_layouts"),
  output: process.stdout,
  console: false,
});

readInterface.on("line", (line) => {
  if (line.includes("=")) {
    if (currentLevel) levels.push(currentLevel);
    const lanesNr = line.indexOf("|") / 3;
    lineIndex = 0;
    currentLevel = {
      layout: [lanesNr, 0x00, 0x00],
      birds: [],
      obstacles: [],
      powerups: [],
      bats: [],
    };
  } else if (line.includes("|")) {
    const items = line.substr(0, line.indexOf("|")).split(/\s+/g);
    items.forEach((item) => {
      const type = item[1];
      switch (item[0]) {
        case "B": {
          currentLevel.bats.push(item);
          break;
        }
        case "O": {
          const obstacle = [lineIndex, ];
          currentLevel.obstacles.push(item);
          break;
        }
        case "P": {
          currentLevel.powerups.push(item);
          break;
        }
      }
    });
    lineIndex++;
  }
});

readInterface.on("close", () => {
  levels.push(currentLevel);
  console.log(levels);
});
