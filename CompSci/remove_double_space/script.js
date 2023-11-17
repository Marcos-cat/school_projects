const textarea = document.querySelector('textarea');
const button = document.querySelector('button');
const output = document.querySelector('p');

button.onclick = function () {
    const text = textarea.value;
    const isNotBlank = s => s !== '';
    output.innerText = text.split(' ').filter(isNotBlank).join(' ');
};
