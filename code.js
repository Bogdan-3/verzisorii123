var x=1;

function myFunction() {
  document.getElementById("GalbenePrimite").innerHTML = x;
  document.getElementById("AlbastrePrimite").innerHTML="100";
  document.getElementById("VerdePrimite").innerHTML="100";
}

function reset_animationBlue() {
  var image = document.getElementById('test3');
  var text = document.getElementById('marquee3');
  
  image.style.animation = 'none';
  text.style.animation = 'none';
  image.offsetHeight; /* trigger reflow */
  text.style.animation = null;
  image.style.animation = null; 
}

function reset_animationGreen() {
  var image = document.getElementById('test1');
  var text = document.getElementById('marquee1');
  
  image.style.animation = 'none';
  text.style.animation = 'none';
  image.offsetHeight; /* trigger reflow */
  text.style.animation = null;
  image.style.animation = null; 
}

function reset_animationYellow() {
  var image = document.getElementById('test2');
  var text = document.getElementById('marquee2');
  
  image.style.animation = 'none';
  text.style.animation = 'none';
  image.offsetHeight; /* trigger reflow */
  text.style.animation = null;
  image.style.animation = null; 
}