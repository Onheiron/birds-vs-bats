var canvas = document.getElementById("gameCanvas");
var urlReader = new GameboyJS.RomAjaxReader();
const game = new GameboyJS.Gameboy(canvas, {
  zoom: 3,
  romReaders: [urlReader],
});
urlReader.loadFromUrl("https://onheiron.github.io/birds-vs-bats/demo.gb");
let startX,
  startY,
  endX,
  endY = 0;
const sensibility = 50;
const body = document.getElementsByTagName("body")[0];
document.addEventListener("keydown", (e) => {
  console.log({ e });
});
document.addEventListener("keyup", (e) => {
  console.log({ e });
});
document.addEventListener("touchstart", (e) => {
  startX = e.touches[0].clientX;
  startY = e.touches[0].clientY;
  console.log({ e, startX, startY });
});
document.addEventListener("touchend", (e) => {
  console.log({ e });
  endX = e.changedTouches[0].clientX;
  endY = e.changedTouches[0].clientY;
  console.log({ e, startX, startY, endX, endY });
  if (endX > startX + sensibility) {
    document.dispatchEvent(
      new KeyboardEvent("keydown", {
        key: "ArrowRight",
        code: "ArrowRight",
        keyCode: 39,
      })
    );
    setTimeout(() => {
      document.dispatchEvent(
        new KeyboardEvent("keyup", {
          key: "ArrowRight",
          code: "ArrowRight",
          keyCode: 39,
        })
      );
    }, 100);
  } else if (endX < startX - sensibility) {
    document.dispatchEvent(
      new KeyboardEvent("keydown", {
        key: "ArrowLeft",
        code: "ArrowLeft",
        keyCode: 37,
      })
    );
    setTimeout(() => {
      document.dispatchEvent(
        new KeyboardEvent("keyup", {
          key: "ArrowLeft",
          code: "ArrowLeft",
          keyCode: 37,
        })
      );
    }, 100);
  } else {
    document.dispatchEvent(
      new KeyboardEvent("keydown", { key: "g", code: "KeyG", keyCode: 71 })
    );
    setTimeout(() => {
      document.dispatchEvent(
        new KeyboardEvent("keyup", { key: "g", code: "KeyG", keyCode: 71 })
      );
    }, 100);
  }
});
