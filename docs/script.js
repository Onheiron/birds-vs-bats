var canvas = document.getElementById("gameCanvas");
var urlReader = new GameboyJS.RomAjaxReader();
new GameboyJS.Gameboy(canvas, { zoom: 2, romReaders: [urlReader] });
urlReader.loadFromUrl("https://onheiron.github.io/birds-vs-bats/demo.gb");
