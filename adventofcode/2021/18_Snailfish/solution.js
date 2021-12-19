#!/usr/bin/node

const fs = require('fs')
const assert = require('assert')
const fullInput = fs.readFileSync(0, 'utf-8')

const lines = fullInput
      .split("\n")
      .filter(x => x.length > 0)
      .map(JSON.parse)

const bufBox = {value: ''}
traverseInOrder(bufBox, lines[0])
console.dir(bufBox)
console.info(`Max level: ${maxLevel(0, lines[0])}`)

const explodingBox = {value: null}
findExploding(explodingBox, 0, lines[0])

console.info('Exploding pair:')
console.dir(explodingBox.value)

{
    const resultContanier = {pair: null, index: -1}
    assert(explodingBox.value !== null)
    findContainer(resultContanier, explodingBox.value, lines[0])
    console.info('Exploding pair container:')
    console.dir(resultContanier)
}

{
    const resultContanier = {pair: null, index: -1}
    assert(explodingBox.value !== null)
    const explodingSeenBox = {value: false}
    lnei(resultContanier, explodingBox.value, explodingSeenBox, lines[0])
    console.info('lnei container:')
    console.dir(resultContanier)
}

{
    const resultContanier = {pair: null, index: -1}
    assert(explodingBox.value !== null)
    const explodingSeenBox = {value: false}
    rnei(resultContanier, explodingBox.value, explodingSeenBox, lines[0])
    console.info('rnei container:')
    console.dir(resultContanier)
}

function traverseInOrder(bufBox, n) {
    assert(typeof bufBox.value === 'string')

    if (Number.isInteger(n)) {
        bufBox.value += n
        return
    }

    assert(Array.isArray(n))
    assert(n.length === 2)

    bufBox.value += '['
    traverseInOrder(bufBox, n[0])
    bufBox.value += ','
    traverseInOrder(bufBox, n[1])
    bufBox.value += ']'
}

function maxLevel(level, n) {
    if (Number.isInteger(n)) return level
    assert(Array.isArray(n))
    assert(n.length === 2)
    return Math.max(maxLevel(level + 1, n[0]), maxLevel(level + 1, n[1]))
}

function findExploding(resultBox, level, n) {
    if (Number.isInteger(n) || resultBox.value !== null) return
    assert(Array.isArray(n))
    assert(n.length === 2)

    if (level === 4) {
        assert(Number.isInteger(n[0]))
        assert(Number.isInteger(n[1]))
        resultBox.value = n
        return
    }

    findExploding(resultBox, level + 1, n[0])
    findExploding(resultBox, level + 1, n[1])
}

function findContainer(resultContanier, needle, n) {
    if (resultContanier.pair !== null || Number.isInteger(n)) return

    if (n[0] == needle) {
        resultContanier.pair = n
        resultContanier.index = 0
        return;
    }

    findContainer(resultContanier, needle, n[0])

    if (n[1] == needle) {
        resultContanier.pair = n
        resultContanier.index = 1
        return;
    }

    findContainer(resultContanier, needle, n[1])
}

// ResultContainer is { pair: Array, index: 0 | 1 }
function lnei(resultContanier, explodingArr, explodingSeenBox, n) {
    assert(Array.isArray(n))
    if (explodingSeenBox.value) return

    if (n[0] === explodingArr) {
        explodingSeenBox.value = true
        return
    }

    if (Number.isInteger(n[0])) {
        if (!explodingSeenBox.value) {
            resultContanier.pair = n
            resultContanier.index = 0
        }
    } else {
        assert(Array.isArray(n[0]))
        lnei(resultContanier, explodingArr, explodingSeenBox, n[0])
    }

    if (n[1] === explodingArr) {
        explodingSeenBox.value = true
        return
    }

    if (Number.isInteger(n[1])) {
        if (!explodingSeenBox.value) {
            resultContanier.pair = n
            resultContanier.index = 1
        }
      } else {
        assert(Array.isArray(n[1]))
        lnei(resultContanier, explodingArr, explodingSeenBox, n[1])
    }
}

// ResultContainer is { pair: Array, index: 0 | 1 }
function rnei(resultContanier, explodingArr, explodingSeenBox, n) {
    assert(Array.isArray(n))
    if (explodingSeenBox.value) return

    if (n[1] === explodingArr) {
        explodingSeenBox.value = true
        return
    }

    if (Number.isInteger(n[1])) {
        if (!explodingSeenBox.value) {
            resultContanier.pair = n
            resultContanier.index = 1
        }
    } else {
        assert(Array.isArray(n[1]))
        rnei(resultContanier, explodingArr, explodingSeenBox, n[1])
    }

    if (n[0] === explodingArr) {
        explodingSeenBox.value = true
        return
    }

    if (Number.isInteger(n[0])) {
        if (!explodingSeenBox.value) {
            resultContanier.pair = n
            resultContanier.index = 0
        }
      } else {
        assert(Array.isArray(n[0]))
        rnei(resultContanier, explodingArr, explodingSeenBox, n[0])
    }
}
