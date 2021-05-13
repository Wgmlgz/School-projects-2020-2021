let frame_counter = 1

let current_frame = 0
let screenLog = document.querySelector('#screen-log');

let zoom = 1

import { btnDown, btnUp, dragTree } from './InputHandler.js'
import { addBlockAndAnim, allLineAndAnim, clearTree, setAnimForward } from './TreeConstructor.js'


setInterval(function(){ 
  zoom = document.getElementById("zoom_slider").value;
  var tree = document.getElementById('tree_ded').style;
  tree.zoom = zoom;
}, 10);

document.addEventListener('mousemove', dragTree);
document.addEventListener('mousedown', btnDown);
document.addEventListener('mouseup', btnUp);


document.querySelector('#bnt_clear').addEventListener('click', clearTree)
document.querySelector('#bnt_prev').addEventListener('click', prevFrame)
document.querySelector('#bnt_next').addEventListener('click', nextFrame)

document.querySelector('#btn_insert').addEventListener('click', insertElement)


document.querySelector('#btn_select_binTree').addEventListener('click', selectBin)
document.querySelector('#btn_select_AVLTree').addEventListener('click', selectAVL)
document.querySelector('#btn_select_RBTree').addEventListener('click', selectRB)
document.querySelector('#btn_select_Treap').addEventListener('click', selectTreap)
document.querySelector('#btn_select_SplayTree').addEventListener('click', selectSplay)

function selectBin() {
  _EXPORT_selectTree(0);
  drawLastTree();
}
function selectAVL() {
  _EXPORT_selectTree(1);
  drawLastTree();
}
function selectRB() {
  _EXPORT_selectTree(2);
  drawLastTree();
}
function selectTreap() {
  _EXPORT_selectTree(3);
  drawLastTree();
}
function selectSplay() {
  _EXPORT_selectTree(4);
  drawLastTree();
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


function insertElement() {
  clearTree()

  let input = document.getElementById('input_insert').value

  _EXPORT_insert(input)
  drawLastTree()
}

function drawLastTree() {
  clearTree()
  _EXPORT_getState(-1)
  var str = readStr()
  drawJsonTreeStr(str)
  _EXPORT_getLines(-1)
  str = readStr()
  drawJsonLinesStr(str)
}
function drawJsonTreeStr(json_string) {
  if (json_string == "") return 
  var data = JSON.parse(json_string);
  for (const property in data) {
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
}

function drawJsonLinesStr(json_string) {
  if (json_string == "") return 
  var data = JSON.parse(json_string);
  for (const property in data) {
    allLineAndAnim(data[property].a, data[property].b, property)
  }
}
// main
function drawJsonTree(json_string) {
  console.log(json_string);
  json_string.json().then(data => {
    for (const property in data) {
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
}

function drawJsonLines(json_string) {
  json_string.json().then(data => {
    for (const property in data) {
      allLineAndAnim(data[property].a, data[property].b, property)
    }
  })
}
function drawTree(num) {
  frame_counter = document.getElementById('frame_counter')

  frame_counter.innerHTML = current_frame
  clearTree()
  fetch('tree_frame_' + num + '.json').then(response => drawJsonTree(response))

  fetch('lines_frame_' + num + '.json').then(response => drawJsonLines(response))
}

function test() {
  _EXPORT_createTestTree(20)
  _EXPORT_outputTestTree()
}

function prevFrame() {
  setAnimForward(false)
  if (current_frame < 0) current_frame = 0
  drawTree(current_frame)
  current_frame -= 1
}

function nextFrame() {
  current_frame += 1
  setAnimForward(true)
  drawTree(current_frame)
}



drawJsonTreeStr('{"1.000000":{"c":"FUCK FUCK","clr":"#000000","x":0,"y":0,"X":0,"Y":0}}')
//drawTree(2);