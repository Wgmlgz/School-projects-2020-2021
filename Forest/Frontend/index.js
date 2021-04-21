var x = 0
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
    newNode.setAttribute('style', `position: absolute;  bottom: ${y}px; right: ${x}px;`)
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
      document.getElementById(name).style.right = x + (x1 - x) * progress + 'px';
      document.getElementById(name).style.bottom = y + (y1 - y) * progress + 'px';
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
