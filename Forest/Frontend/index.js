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
  
    if (timeFraction < 1) { requestAnimationFrame(animate); }

  });
}

function addBlock(name, content, x, y) {
    var newNode = document.createElement('div');
    // newNode.className = 'tree_node';
    newNode.setAttribute('id', name)
    newNode.setAttribute('style', `position: absolute;  top: ${y}px; left: ${x}px;`)

    newNode.innerHTML = `<p class="tree_node"\>${content}</p>`

    tree.appendChild(newNode);
}

function addBlockAndAnim(name, content, x, y, x1, y1) {
  addBlock(name,content,x,y)
  animate({
    duration: anim_time,
    timing: function (timeFraction) {
      let c = 3
      // if (timeFraction < 0.5) return 0
      if (timeFraction < 0.5) return Math.pow(timeFraction * 2, c) / 2
      else return Math.pow(timeFraction * 2 - 2, c) / 2 + 1
      // else return 0
    },
    draw: function(progress) {
      document.getElementById(name).style.left = x + (x1 - x) * progress + 'px';
      document.getElementById(name).style.top = y + (y1 - y) * progress + 'px';
    }
  });  
}

function refreshLinePos(line, a, b) {
  let as = document.getElementById(a).style
  let bs = document.getElementById(b).style

  var posax = Number.parseInt(as.left) - 35
  var posay = Number.parseInt(as.top)- 5
  
  //last dot
  var posbx = Number.parseInt(bs.left)- 35
  var posby = Number.parseInt(bs.top)- 5

  //temp calculation variables
  var centerx;
  var centery;
  var distance;
  var angle;
  
  //find center points;
  centerx = (posax+posbx)/2;
  centery = (posay+posby)/2;
  
  var angle = Math.atan2(posay-posby,posax-posbx)* 180 / Math.PI;
  distance = Math.sqrt(Math.pow((posbx - posax), 2) + Math.pow((posby - posay), 2));
  
  $(line).css("width", distance +"px");
  $(line).css("transform"," rotate("+angle+"deg)");
  $(line).css("top",centery  - ($(line).height()/2)+(100/2));
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
  var line = addLine(a, b, property)
  animate({
    duration: anim_time,
    timing: function(timeFraction) {
        return timeFraction
    },
    draw: function(progress) {
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
        data[property].Y
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
  is_down = true;
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

