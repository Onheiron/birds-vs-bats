var canvas = document.getElementById("gameCanvas");
new GameboyJS.Gameboy(canvas, { zoom: 2, romReaders: [ (new GameboyJS.RomAjaxReader()).loadFromUrl("https://onheiron.github.io/birds-vs-bats/demo.gb") ] });