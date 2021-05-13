let offset_x = 0
let offset_y = 0

let down_x = 0
let down_y = 0

let is_down = false


let start = true

export function btnDown(e) {
  if (e.screenY > 200) {
    is_down = true;
  }
  down_x = e.screenX
  down_y = e.screenY
  
}
export function btnUp(e) {
  is_down = false;
  let st = document.getElementById('tree').style
  offset_x = parseInt(st.left)
  offset_y = parseInt(st.top)
}
export function dragTree(e) {
  let x = e.screenX
  let y = e.screenY

  if (is_down || start) {
    let st = document.getElementById('tree').style
    if (start) {
      st.left = 0 + 'px'
      st.top = 0 + 'px'
    } else {
      let zoom = document.getElementById("zoom_slider").value;
      st.left = (x - down_x) * (1 / zoom) + offset_x + 'px'
      st.top = (y - down_y) * (1 / zoom)+ offset_y + 'px'
    }

    start = false
  }
}
   
// module.exports = { btnDown, btnUp, dragTree }
// export { btnDown, btnUp, dragTree };