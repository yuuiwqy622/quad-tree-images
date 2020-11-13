function selectCell(e) {
    e.preventDefault()

    let c = e.target.classList
    if (c.contains('selected')) {
        c.remove('selected')
        return
    }

    c.add('selected')
}

function createTable() {
    let size = parseInt(document.querySelector('#val').value)
    let f = document.createDocumentFragment()

    for (let i = 0; i < size; ++i) {
        let tr = document.createElement('tr')
        for (let j = 0; j < size; ++j) {
            let td = document.createElement('td')
            td.textContent = 0
            td.addEventListener('wheel', (e) => { e.target.textContent = e.target.textContent == '1' ? '0' : '1' })
            td.addEventListener('contextmenu', selectCell)
            tr.append(td)
        }

        f.append(tr)
    }

    let t = document.querySelector('table')
    t.append(f)
}


document.addEventListener('DOMContentLoaded', (e) => {
    document.getElementById('start').addEventListener('click', createTable)
})