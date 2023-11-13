/** @type HTMLButtonElement */
const answerButton = document.querySelector('#answer');
/** @type HTMLButtonElement */
const tipsButton = document.querySelector('#tips');
/** @type HTMLButtonElement */
const valButton = document.querySelector('#val');

const answerOut = document.querySelector('#ans-out');
const tipsOut = document.querySelector('#tips-out');
const out = document.querySelector('#out');

answerButton.onclick = function () {
    alert('Show the Answer');

    showAnswer();
};

tipsButton.onclick = function () {
    const n = Math.floor(Math.random() * tips.length);

    showTip(n);
};

valButton.onclick = function () {
    const x = 5;

    squareIt(x);
};

function showAnswer() {
    answerOut.innerHTML = 'The Capital of Michigan is Lansing';
}

/** @param {number} n */
function squareIt(n) {
    out.innerHTML = n * n;
}

const tips = [
    'Keep away from magnets',
    'Keep away from extreme heat',
    'Avoid touching the surface',
];

/** @param {number} n */
function showTip(n) {
    tipsOut.innerHTML = tips[n];
}
