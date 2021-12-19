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

const lnei = makeFindNei([0, 1])
const rnei = makeFindNei([1, 0])

{
    const resultContanier = {pair: null, index: -1}
    assert(explodingBox.value !== null)
    findContainer(resultContanier, x => x === explodingBox.value, lines[0])
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

function explode(n) {
    const explodingBox = {value: null}
    findExploding(explodingBox, 0, n)
    assert(explodingBox.value !== null)

    const A = explodingBox.value[0]
    const B = explodingBox.value[1]

    const explodingPairContanier = {pair: null, index: -1}
    findContainer(explodingPairContanier, x => x === explodingBox.value, n)

    const lneiContanier = {pair: null, index: -1}
    lnei(lneiContanier, explodingBox.value, {value: false}, n)

    const rneiContanier = {pair: null, index: -1}
    rnei(rneiContanier, explodingBox.value, {value: false}, n)
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

function findContainer(resultContanier, pred, n) {
    if (resultContanier.pair !== null || Number.isInteger(n)) return

    for (let i of [0, 1]) {
        if (pred(n[i])) {
            resultContanier.pair = n
            resultContanier.index = i
            return;
        }

        findContainer(resultContanier, pred, n[i])
    }
}

// ResultContainer is { pair: Array, index: 0 | 1 }
function makeFindNei(indices) {
    return function recur(resultContanier, explodingArr, explodingSeenBox, n) {
        assert(Array.isArray(n))
        if (explodingSeenBox.value) return

        for (let i of indices) {
            if (n[i] === explodingArr) {
                explodingSeenBox.value = true
                return
            }

            if (Number.isInteger(n[i])) {
                if (!explodingSeenBox.value) {
                    resultContanier.pair = n
                    resultContanier.index = i
                }
            } else {
                assert(Array.isArray(n[i]))
                recur(resultContanier, explodingArr, explodingSeenBox, n[i])
            }
        }
    }
}
