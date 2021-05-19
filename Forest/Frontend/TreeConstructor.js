let anim_time = 500 
export var anim_forward = true
var anim_progress = 1
var current_frame = 0

function animate({ duration, draw, timing }) {
  let start = performance.now();
  let anim_frame = current_frame

  requestAnimationFrame(function animate(time) {
    let timeFraction = (time - start) / duration;
    if (timeFraction > 1) timeFraction = 1;
    timeFraction = anim_progress - anim_frame
    if (timeFraction > 1 || timeFraction < 0) return

    draw(timing(timeFraction));
    if (timeFraction != 1) { requestAnimationFrame(animate); }

  });
}

function addBlock(name, content, x, y, color) {
  var newNode = document.createElement('p');
  newNode.className = 'tree_node';
  newNode.setAttribute('id', name)
  newNode.setAttribute('style', `position:absolute;top:${y}px;left:${x}px;border-color:${color};background-color:${color}`)

  newNode.innerHTML = `${content}`

  tree.appendChild(newNode);
}

export function addBlockAndAnim(name, content, x, y, x1, y1, color) {
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
      }catch {}
    }
  });  
}

function refreshLinePos(line, a, b) {
  try {
    let as = document.getElementById(a).style
    let bs = document.getElementById(b).style

    var posax = Number.parseInt(as.left) - 25
    var posay = Number.parseInt(as.top)
  
    var posbx = Number.parseInt(bs.left) - 25
    var posby = Number.parseInt(bs.top)

    var centerx;
    var centery;
    var distance;
    var angle;
  
    centerx = (posax + posbx) / 2;
    centery = (posay + posby) / 2;
  
    var angle = Math.atan2(posay - posby, posax - posbx) * 180 / Math.PI;
    distance = Math.sqrt(Math.pow((posbx - posax), 2) + Math.pow((posby - posay), 2));

    $(line).css("width", distance + "px");
    $(line).css("transform", " rotate(" + angle + "deg)");
    $(line).css("top", centery - ($(line).height() / 2) + (100 / 2));
    $(line).css("left", centerx - ($(line).width() / 2) + (100 / 2));
  } catch{
    
  }
}
function addLine(a, b, property) {
  var line = document.createElement('div');
  line.className = 'line';

  refreshLinePos(line, a, b)

  tree.appendChild(line);
  return line
}
export function allLineAndAnim(a, b, property) {
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

export function setAnimForward(new_val) {
  anim_forward = new_val
}
export function clearTree() {
  tree.innerHTML = ''
}
export function setAnimProgress(tmp, frame) {
  current_frame = frame
  anim_progress = tmp
}