var main_view;
var controls_view;
window.addEventListener('load', (event) => {
  main_view = document.getElementById("main_view");
  controls_view = document.getElementById("controls_view");
});

function showControls(active) {
	if (active) {
		main_view.style.display = "none";
		controls_view.style.display = "inline";
	}
	else {
		main_view.style.display = "inline";
		controls_view.style.display = "none";
	}
}