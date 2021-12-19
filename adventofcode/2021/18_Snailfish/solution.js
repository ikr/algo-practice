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

function recurExplode(level, lneiArr, rneiAdditionBox, n) {
    assert(Array.isArray(n))
    assert(n.length === 2)

    if (level < 4) {
        if (Array.isArray(n[0])) {
            recurExplode(level + 1, lneiArr, rneiAdditionBox, n[0])
        } else {
            assert(Number.isInteger(n[0]))
            lneiArr = n
        }

        if (Array.isArray(n[1])) {
            recurExplode(level + 1, lneiArr, rneiAdditionBox, n[1])
        } else {
            assert(Number.isInteger(n[1]))
            assert(Number.isInteger(rneiAdditionBox.value))

            if (rneiAdditionBox.value > 0) {
                n[1] += rneiAdditionBox.value
                rneiAdditionBox.value = 0
            }
        }

        return
    }

    assert(level === 4)
    if (Array.isArray(n[0])) {

    } else {
        assert(Number.isInteger(n[0]))
     }

    if (Array.isArray(n[1])) {

    } else {
        assert(Number.isInteger(n[1]))

    }
}
