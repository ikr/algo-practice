#!/usr/bin/node

const fs = require('fs')
const assert = require('assert')
const fullInput = fs.readFileSync(0, 'utf-8')

const lines = fullInput
      .split("\n")
      .filter(x => x.length > 0)
      .map(JSON.parse)

const lnei = makeFindNei([0, 1])
const rnei = makeFindNei([1, 0])

console.info(JSON.stringify(magnitude(snailfish_numbers_sum(lines))))

function clone(x) {
    return JSON.parse(JSON.stringify(x))
}

function snailfish_numbers_sum(ns) {
    let x = ns[0]
    for (let i = 1; i < ns.length; ++i) {
        x = reduce_snailfish_number([x, ns[i]])
    }
    return x
}

function magnitude(n) {
    if (Number.isInteger(n)) return n
    assert(Array.isArray(n))
    assert(n.length === 2)
    return 3 * magnitude(n[0]) + 2 * magnitude(n[1])
}

function reduce_snailfish_number(src) {
    let n = clone(src)
    for (;;) {
        if (maxLevel(0, n) > 4) {
            n = explode(n);
            continue
        }

        const splitnumContanier = {pair: null, index: -1}
        findContainer(splitnumContanier, x => (Number.isInteger(x) && x > 9), n)

        if (splitnumContanier.pair !== null) {
            splitnumContanier.pair[splitnumContanier.index] = split_number(
                splitnumContanier.pair[splitnumContanier.index]
            )
            continue
        }

        break
    }
    return n
}

function split_number(x) {
    assert(Number.isInteger(x))
    const a = Math.floor(x / 2)
    const b = x - a
    return [a, b]
}

function explode(n) {
    const explodingBox = {value: null}
    findExploding(explodingBox, 0, n)
    assert(explodingBox.value !== null)

    const A = explodingBox.value[0]
    assert(Number.isInteger(A))
    const B = explodingBox.value[1]
    assert(Number.isInteger(B))

    const explodingPairContanier = {pair: null, index: -1}
    findContainer(explodingPairContanier, x => x === explodingBox.value, n)

    const lneiContanier = {pair: null, index: -1}
    lnei(lneiContanier, explodingBox.value, {value: false}, n)

    const rneiContanier = {pair: null, index: -1}
    rnei(rneiContanier, explodingBox.value, {value: false}, n)

    if (lneiContanier.pair !== null) {
        lneiContanier.pair[lneiContanier.index] += A
    }

    if (rneiContanier.pair !== null) {
        rneiContanier.pair[rneiContanier.index] += B
    }

    explodingPairContanier.pair[explodingPairContanier.index] = 0
    return n
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
        if (resultContanier.pair === null && pred(n[i])) {
            resultContanier.pair = n
            resultContanier.index = i
            return
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
