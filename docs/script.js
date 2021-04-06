var canvas = document.getElementById("gameCanvas");
var urlReader = new GameboyJS.RomAjaxReader();
new GameboyJS.Gameboy(canvas, { zoom: 3, romReaders: [urlReader] });
urlReader.loadFromUrl("https://onheiron.github.io/birds-vs-bats/demo.gb");
