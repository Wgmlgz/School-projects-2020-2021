let offset_x = 0
let offset_y = 0


let is_down = false

function animate({duration, draw, timing}) {
  let start = performance.now();
  
  requestAnimationFrame(function animate(time) {
    let timeFraction = (time - start) / duration;
    if (timeFraction > 1) timeFraction = 1;
  
    draw(timing(timeFraction));
  
    if (timeFraction < 1) { requestAnimationFrame(animate); }

  });
}

function addBlock(name, content, x, y) {
    var newNode = document.createElement('div');
    newNode.className = name;
    newNode.setAttribute('id', name)
    newNode.setAttribute('style', `position: absolute;  top: ${y}px; left: ${x}px;`)

    //newNode.innerHTML = '<img class="anime" src="images/a.jpg" /><p>fuck</p>';
    newNode.innerHTML = `\
    <p style="border:4px; border-style:solid; border-radius: 10px; border-color:#b434eb;\
    padding: 0.3em; font-family:consolas; font-size: 1.2em; background-color: white"\>${content}</p>`

    tree.appendChild(newNode);
}

function addBlockAndAnim(name, content, x, y, x1, y1) {
  addBlock(name,content,x,y)
  animate({
    duration: 500,
    timing: function(timeFraction) {
        return timeFraction
    },
    draw: function(progress) {
      document.getElementById(name).style.left = x + (x1 - x) * progress + 'px';
      document.getElementById(name).style.top = y + (y1 - y) * progress + 'px';
    }
  });  
}
function addLine(a, b) {
  let x1 = document.getElementById(a).style.left
  let y1 = document.getElementById(a).style.top

  let x2 = document.getElementById(b).style.left
  let y2 = document.getElementById(b).style.top

  
  var newNode = document.createElement('svg');
  newNode.setAttribute('style', `position: absolute;`)
  //newNode.setAttribute('style', `position: absolute;  top: ${y}px; left: ${x}px;`)
  newNode.innerHTML = `\
  <line x1="${x1}" y1="${y1}" x2="${x2}" y2="${y2}"\
  style="stroke:rgb(255,0,0);stroke-width:2" />\
  `
}
// main
fetch('tree_frame_0.json').then(response => response.json()).then(data => {
    // console.log(data)
    for (const property in data) {
        console.log(`${property}: ${data[property]}`);
        addBlockAndAnim(
            property,
            data[property].content,
            data[property].x,
            data[property].y,
            data[property].x1,
            data[property].y1
        )
    }
    
})

fetch('lines_frame_0.json').then(response => response.json()).then(data => {
    //console.log(data)
    for (const property in data) {
      console.log(`${property} + ${data[property]}`)
      a = data[property].a
      b = data[property].b
      console.log(a)
      console.log(b)
      // addline(property, data[property]);
      let as = document.getElementById(a).style
      let bs = document.getElementById(b).style
      let x1 = Number.parseInt(as.left) - 30
      let y1 = Number.parseInt(as.top)- 5

      let x2 = Number.parseInt(bs.left)- 30
      let y2 = Number.parseInt(bs.top)- 5

      
      var line = document.createElement('div');
      line.className = property;

      var posax = x1
      var posay = y1
      
      //last dot
      var posbx = x2
      var posby = y2
      console.log(x1)
      console.log(y1)
      console.log(x2)
      console.log(y2)

      //temp calculation variables
      var centerx;
      var centery;
      var distance;
      var angle;
      
      //find center points;
      centerx = (posax+posbx)/2;
      centery = (posay+posby)/2;
      
      //angle 
      var angle = Math.atan2(posay-posby,posax-posbx)* 180 / Math.PI;
      
      //distance
      distance = Math.sqrt(    Math.pow((posbx-posax),2) + Math.pow((posby-posay),2)    );
      
      console.log(distance)
      console.log(angle)
      //bring all the work together

      $(line).css("width", distance +"px");
      $(line).css("transform"," rotate("+angle+"deg)");
      $(line).css("top",centery  - ($(line).height()/2)+(100/2));
      $(line).css("left", centerx - ($(line).width() / 2) + (100 / 2));
      $(line).css("background-color", "white")
      $(line).css('height', '5px')
      $(line).css('position', 'absolute')
      $(line).css('z-index', '-10')

      tree.appendChild(line);
    }
    
})


let last_x = 0
let last_y = 0

let down_x = 0
let down_y = 0
let start = true

let screenLog = document.querySelector('#screen-log');
document.addEventListener('mousemove', logKey);
document.addEventListener('mousedown', btnDown);
document.addEventListener('mouseup', btnUp);

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
function logKey(e) {
  if (is_down || start) {
    st = document.getElementById('tree').style
    if (start) {
      st.left = 0 + 'px'
      st.top = 0 + 'px'
    } else {
      st.left = e.screenX - down_x + offset_x + 'px'
      st.top = e.screenY - down_y + offset_y + 'px'
    }
    last_x = e.screenX
    last_y = e.screenY

    start = false
  }
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
