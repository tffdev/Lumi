var canvas = document.getElementById("lumi-logo-canvas");
var buttons = document.getElementsByClassName("button");
var titlebox = document.getElementsByClassName("title-box")[0];
var ctx = canvas.getContext("2d");

var nebula_img = new Image();
nebula_img.src = "nebula.jpg";

var stars_img = new Image();
stars_img.src = "stars.png";

var lumi_logo = new Image();
lumi_logo.src = "lumi_logo.png";

var scrollx = 0;
var scrolly = 0;
var draw_iteration = 0;

function draw() {
  scrolly -= 0.5;
  scrollx += 0.1;
  ctx.globalCompositeOperation = "source-over";
  ctx.drawImage(nebula_img, scrollx%nebula_img.width, scrolly%nebula_img.height);
  ctx.drawImage(nebula_img, scrollx%nebula_img.width, scrolly%nebula_img.height + nebula_img.height);
  ctx.drawImage(nebula_img, scrollx%nebula_img.width - nebula_img.width, scrolly%nebula_img.height);
  ctx.drawImage(nebula_img, scrollx%nebula_img.width - nebula_img.width, scrolly%nebula_img.height + nebula_img.height);

  ctx.drawImage(stars_img, (scrollx*0.5)%stars_img.width, (scrolly*0.5)%stars_img.height);
  ctx.drawImage(stars_img, (scrollx*0.5)%stars_img.width, (scrolly*0.5)%stars_img.height + stars_img.height);
  ctx.drawImage(stars_img, (scrollx*0.5)%stars_img.width - stars_img.width, (scrolly*0.5)%stars_img.height);
  ctx.drawImage(stars_img, (scrollx*0.5)%stars_img.width - stars_img.width, (scrolly*0.5)%stars_img.height + stars_img.height);

  ctx.globalCompositeOperation = "destination-in";
  ctx.drawImage(lumi_logo, 0, 0, canvas.width, lumi_logo.height * (canvas.width/lumi_logo.width));
}

function avg_col(canv_data) {
  var blockSize = 50;
  var rgb = {r:0,g:0,b:0};
  var count = 0;
  var i = -4;
  length = canv_data.data.length;
  while ((i += blockSize * 4) < length) {
    ++count;
    rgb.r += canv_data.data[i];
    rgb.g += canv_data.data[i+1];
    rgb.b += canv_data.data[i+2];
  }
  rgb.r = ~~(rgb.r/count);
  rgb.g = ~~(rgb.g/count);
  rgb.b = ~~(rgb.b/count);

  return rgb;
}

setInterval(draw, 15);