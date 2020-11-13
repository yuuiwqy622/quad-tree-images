var len = 0, idx1 = 0, idx2 = 0

function switchVal(e) {
    let t = e.target
    t.textContent = t.textContent == '1' ? '0' : '1'
}

function appendTd(tr, shift, digit) {
    let td = document.createElement('td')
    td.addEventListener('contextmenu', selectCell)
    td.addEventListener('wheel', switchVal)
    td.textContent = digit >> shift & 1
    tr.append(td)
}

function addLine(l) {
    let tr = document.createElement('tr')

    for (c of l) {
        let digit = parseInt(c, 16)
        appendTd(tr, 3, digit)
        appendTd(tr, 2, digit)
        appendTd(tr, 1, digit)
        appendTd(tr, 0, digit)
    }

    let t = document.querySelector('table')
    t.append(tr)
}

function selectCell(e) {
    e.preventDefault()

    let c = e.target.classList
    if (c.contains('selected')) {
        c.remove('selected')
        return
    }

    c.add('selected')
}

function createTable(lines) {
    addLine(lines[0]), addLine(lines[1])

    let t = document.querySelector('table')
    let tr = document.createElement('tr')
    let rows = t.children
    let maxl = Math.max(rows[0].children.length, rows[1].children.length)

    for (let i = 0; i < 2 * maxl; ++i) {
        let td = document.createElement('td')
        td.addEventListener('contextmenu', selectCell)
        td.addEventListener('wheel', switchVal)
        tr.append(td)
    }
    t.append(tr)
}

function intersection(n1, n2) {
    let rows = document.querySelector('table').children
    let line1 = rows[0].children
    let line2 = rows[1].children
    let inter = rows[2].children

    if (line1[idx1].textContent == '1' && line2[idx2].textContent == '1') {
        inter[len++].textContent = '1'
        inter[len++].textContent = (parseInt(line1[idx1 + 1].textContent) & parseInt(line2[idx2 + 1].textContent)).toString()
        line1[idx1].classList.remove('selected')
        line2[idx2].classList.remove('selected')
        idx1 += 2 * n1
        idx2 += 2 * n2
        idx1 *= idx1 < line1.length
        idx2 *= idx2 < line2.length
        line1[idx1].classList.add('selected')
        line2[idx2].classList.add('selected')
        return
    }

    inter[len++].textContent = 0
    n1 = line1[idx1].textContent == '0'
    n2 = line2[idx2].textContent == '0'
    line1[idx1].classList.remove('selected')
    line2[idx2].classList.remove('selected')
    idx1 += n1, idx2 += n2
    line1[idx1].classList.add('selected')
    line2[idx2].classList.add('selected')
    let q1 = len
    intersection(n1, n2)
    let q2 = len
    intersection(n1, n2)
    let q3 = len
    intersection(n1, n2)
    let q4 = len
    intersection(n1, n2)

    if (inter[q1].textContent == '1' && inter[q2].textContent == '1' && inter[q3].textContent == '1' && inter[q4].textContent == '1' && inter[q1 + 1] == inter[q2 + 1] && inter[q1 + 1] == inter[q3 + 1] && inter[q1 + 1] == inter[q4 + 1]) {
        inter[q1 - 1].textContent = '1'
        inter[q1].textContent = inter[q1 + 1].textContent
        len -= 7
    }

}

function start() {
    let rows = document.querySelector('table').children
    for (; rows[0].children[idx1].textContent == '0'; ++idx1);
    for (; rows[1].children[idx2].textContent == '0'; ++idx2);
    ++idx1, ++idx2

    rows[0].children[idx1].classList.add('selected')
    rows[1].children[idx2].classList.add('selected')
    intersection(0, 0)
}

function readFile(e) {
    let f = e.target.files[0]
    if (!f) return

    let rd = new FileReader()
    rd.onload = (e) => {
        let lines = e.target.result.split(/[\r\n]+/g)
        console.log(lines)
        createTable(lines)
    }
    rd.readAsText(f)
}

document.addEventListener('DOMContentLoaded', (e) => {
    document.getElementById('file-input').addEventListener('change', readFile)
    document.getElementById('start').addEventListener('click', start)
})