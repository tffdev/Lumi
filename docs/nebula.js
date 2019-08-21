var canvas = document.getElementById("c");
var ctx = canvas.getContext("2d");
var nebula_img = new Image();
nebula_img.src = "nebula.jpg";

var lumi_logo = new Image();
lumi_logo.src = "lumi_logo.svg";
var scrollx = 0;
var scrolly = 0;
function draw() {
  scrolly -= 0.5;
  scrollx += 0.1;
  ctx.globalCompositeOperation = "source-over";
  ctx.drawImage(nebula_img, scrollx%nebula_img.width, scrolly%nebula_img.height);
  ctx.drawImage(nebula_img, scrollx%nebula_img.width, scrolly%nebula_img.height + nebula_img.height);
  ctx.drawImage(nebula_img, scrollx%nebula_img.width - nebula_img.width, scrolly%nebula_img.height);
  ctx.drawImage(nebula_img, scrollx%nebula_img.width - nebula_img.width, scrolly%nebula_img.height + nebula_img.height);
  ctx.globalCompositeOperation = "destination-in";
  ctx.drawImage(lumi_logo, 0, 0, canvas.width, lumi_logo.height * (canvas.width/lumi_logo.width));
}
setInterval(draw, 15);