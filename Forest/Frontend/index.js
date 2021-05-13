let offset_x = 0
let offset_y = 0

let is_down = false
let anim_time = 500 

let last_x = 0
let last_y = 0

let down_x = 0
let down_y = 0
let start = true

let current_frame = 0
let anim_forward = true
let screenLog = document.querySelector('#screen-log');

document.addEventListener('mousemove', logKey);
document.addEventListener('mousedown', btnDown);
document.addEventListener('mouseup', btnUp);

function animate({duration, draw, timing}) {
  let start = performance.now();
  
  requestAnimationFrame(function animate(time) {
    let timeFraction = (time - start) / duration;
    if (timeFraction > 1) timeFraction = 1;
  
    if (anim_forward == false) timeFraction = 1 - timeFraction

    draw(timing(timeFraction));
  
    if (true) { requestAnimationFrame(animate); }

  });
}

function addBlock(name, content, x, y, color) {
  console.log(color);
  var newNode = document.createElement('p');
  newNode.className = 'tree_node';
  newNode.setAttribute('id', name)
  newNode.setAttribute('style', `position:absolute;top:${y}px;left:${x}px;border-color:${color};background-color:${color}`)

  newNode.innerHTML = `${content}`

  tree.appendChild(newNode);
}

function addBlockAndAnim(name, content, x, y, x1, y1, color) {
  addBlock(name,content,x,y, color)
  animate({
    duration: anim_time,
    timing: function (timeFraction) {
      let c = 3
      // if (timeFraction < 0.5) return 0
      if (timeFraction < 0.5) return Math.pow(timeFraction * 2, c) / 2
      else return Math.pow(timeFraction * 2 - 2, c) / 2 + 1
      // else return 0
    },
    draw: function (progress) {
      try {
        var this_st = document.getElementById(name).style;
        this_st.left = (x + (x1 - x) * progress) + 'px';
        this_st.top = (y + (y1 - y) * progress) + 'px';
        var sliderv = document.getElementById("zoom_slider").value;
        var tree = document.getElementById('tree_ded').style;
        tree.zoom = sliderv;
      }catch {}
    }
  });  
}

function refreshLinePos(line, a, b) {
    console.log("rfr");
    console.log(a);
    console.log(b);
    let as = document.getElementById(a).style
    let bs = document.getElementById(b).style

    var posax = Number.parseInt(as.left) - 25
    var posay = Number.parseInt(as.top)
  
    //last dot
    var posbx = Number.parseInt(bs.left) - 25
    var posby = Number.parseInt(bs.top)

    //temp calculation variables
    var centerx;
    var centery;
    var distance;
    var angle;
  
    //find center points;
    centerx = (posax + posbx) / 2;
    centery = (posay + posby) / 2;
  
    var angle = Math.atan2(posay - posby, posax - posbx) * 180 / Math.PI;
    distance = Math.sqrt(Math.pow((posbx - posax), 2) + Math.pow((posby - posay), 2));

    $(line).css("width", distance + "px");
    $(line).css("transform", " rotate(" + angle + "deg)");
    $(line).css("top", centery - ($(line).height() / 2) + (100 / 2));
    $(line).css("left", centerx - ($(line).width() / 2) + (100 / 2));
}
function addLine(a, b, property) {
  var line = document.createElement('div');
  line.className = 'line';

  refreshLinePos(line, a, b)

  tree.appendChild(line);
  return line
}
function allLineAndAnim(a, b, property) {
  console.log("dad");
  var line = addLine(a, b, property)
  animate({
    duration: anim_time,
    timing: function (timeFraction) {
      return timeFraction
    },
    draw: function (progress) {
      refreshLinePos(line, a, b)
    }
  });
}
function clearTree() {
  tree.innerHTML = ''
}
// main

function drawTree(num) {
  frame_counter = document.getElementById('frame_counter')

  frame_counter.innerHTML = current_frame
  clearTree()
  fetch('tree_frame_' + num + '.json').then(response => response.json()).then(data => {
    // console.log(data)
    for (const property in data) {
      console.log(`${property}: ${data[property]}`);
      addBlockAndAnim(
        property,
        data[property].c,
        data[property].x,
        data[property].y,
        data[property].X,
        data[property].Y,
        data[property].clr
      )
    }
  })

  fetch('lines_frame_' + num + '.json').then(response => response.json()).then(data => {
    //console.log(data)
    for (const property in data) {
      console.log(`${property} + ${data[property]}`)
      a = data[property].a
      b = data[property].b
      console.log(a)
      console.log(b)
      allLineAndAnim(a, b, property)
    }
    
  })
}
function btnDown(e) {
  console.log(e.screenY);
  if (e.screenY > 200) {
    is_down = true;
  }
  down_x = e.screenX
  down_y = e.screenY
  
}
function btnUp(e) {
  is_down = false;
  st = document.getElementById('tree').style
  offset_x = parseInt(st.left)
  offset_y = parseInt(st.top)
}
function dragTree(x, y) {
  // console.log(x, y)
  if (is_down || start) {
    st = document.getElementById('tree').style
    if (start) {
      st.left = 0 + 'px'
      st.top = 0 + 'px'
    } else {
      st.left = x - down_x + offset_x + 'px'
      st.top = y - down_y + offset_y + 'px'
    }
    last_x = x
    last_y = y

    start = false
  }
}
function logKey(e) {
  dragTree(e.screenX, e.screenY)
  // console.log(`
  //   Screen X/Y: ${e.screenX}, ${e.screenY}
  //   Client X/Y: ${e.clientX}, ${e.clientY}`)
}
        
 function placeDiv(x_pos, y_pos) {
  var d = document.getElementById('TextHidden');
  d.style.position = "absolute";
  d.style.left = x_pos+'px';
  d.style.top = y_pos+'px';
}

function test() {
  _EXPORT_createTestTree(20)
  _EXPORT_outputTestTree()
}

function prevFrame() {
  anim_forward = false
  if (current_frame < 0) current_frame = 0
  drawTree(current_frame)
  current_frame -= 1
}

function nextFrame() {
  current_frame += 1
  anim_forward = true
  drawTree(current_frame)
}


// КОСТЫЛЬ!!!!
function readStr() {
  let buff = "";

  let rres = _EXPORT_readChar();
    if (rres == 0) return buff;
  buff += String.fromCharCode(rres);

  while (true) {
    rres = _EXPORT_readChar();
    if (rres == 0) return buff;
    buff += String.fromCharCode(rres);
  }
}

drawTree(2);