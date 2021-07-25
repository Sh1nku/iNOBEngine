let lives_element;
let ship_img = "../ship/ship_icon.png"

window.addEventListener('load', (event) => {
    lives_element = document.getElementById("lives");
});

function updateLives(count) {
    lives_element.innerHTML = "";
    for(let i = 0; i < count; i++) {
        lives_element.innerHTML += "<img src='" + ship_img + "'></img>";
    }
}