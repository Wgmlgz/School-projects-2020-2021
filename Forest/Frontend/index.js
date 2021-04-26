let offset_x = 0
let offset_y = 0


let is_down = false

function animate({duration, draw, timing}) {

    let start = performance.now();
  
    requestAnimationFrame(function animate(time) {
      let timeFraction = (time - start) / duration;
      if (timeFraction > 1) timeFraction = 1;
  
      let progress = timing(timeFraction)
  
      draw(progress);
  
      if (timeFraction < 1) {
        requestAnimationFrame(animate);
      }
  
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
    padding: 0.3em; font-family:consolas; font-size: 1.2em;">${content}</p>`
    ;
    tree.appendChild(newNode);
};
function addBlockAndAnim(name, content, x, y, x1, y1) {
  addBlock(name, x, y)
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
// main
fetch('frame0.json').then(response => response.json()).then(data => {
    console.log(data)
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

let last_x = 0
let last_y = 0

let down_x = 0
let down_y = 0

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
  if (is_down) {
    st = document.getElementById('tree').style
    st.left = e.screenX - down_x + offset_x + 'px'
    st.top  = e.screenY - down_y + offset_y + 'px'

    last_x = e.screenX
    last_y = e.screenY
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