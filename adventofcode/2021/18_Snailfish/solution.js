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

lines.forEach(n => {
    const src = JSON.stringify(n)

    const bufBox = {value: ''}
    traverseInOrder(bufBox, n)
    assert.strictEqual(bufBox.value, src)
})

function clone(x) {
    return JSON.parse(JSON.stringify(x))
}

console.info("SF nums sum:")
console.info(JSON.stringify(snailfish_numbers_sum(lines)))

console.info("SF nums sum magnitude:")
console.info(JSON.stringify(magnitude(snailfish_numbers_sum(lines))))

assert.strictEqual(magnitude([[1,2],[[3,4],5]]), 143)
assert.strictEqual(magnitude([[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]), 3488)

assert.deepEqual(explode([[[[[9,8],1],2],3],4]), [[[[0,9],2],3],4])
assert.deepEqual(explode([7,[6,[5,[4,[3,2]]]]]), [7,[6,[5,[7,0]]]])
assert.deepEqual(explode([[6,[5,[4,[3,2]]]],1]), [[6,[5,[7,0]]],3])
assert.deepEqual(explode([[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]), [[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]])
assert.deepEqual(explode([[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]), [[3,[2,[8,0]]],[9,[5,[7,0]]]])

assert.deepEqual(
    reduce_snailfish_number([[[[[4,3],4],4],[7,[[8,4],9]]], [1,1]]),
    [[[[0,7],4],[[7,8],[6,0]]],[8,1]]
)

assert.deepEqual(explode([[1,[5,[7,[2,5]]]],[[[[4,6],3],2],4]]), [[1,[5,[9,0]]],[[[[9,6],3],2],4]])
assert.deepEqual(explode([[1,[5,[9,0]]],[[[[9,6],3],2],4]]), [[1,[5,[9,9]]],[[[0,9],2],4]])
assert.deepEqual(explode([1,[2,[3,[4,[5,6]]]]]), [1,[2,[3,[9,0]]]])

assert.deepEqual(
    reduce_snailfish_number(
        [
            [[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]],
            [7,[5,[[3,8],[1,4]]]]
        ]
    ),
    [[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]],
    'The first non-trivial reduction I saw failing'
)

function snailfish_numbers_sum(ns) {
    let x = ns[0]
    // console.info(`  ${JSON.stringify(x)}`)

    for (let i = 1; i < ns.length; ++i) {
        // console.info(`+ ${JSON.stringify(ns[i])}`)
        x = reduce_snailfish_number([x, ns[i]])
        // console.info(`= ${JSON.stringify(x)}\n`)
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
            const n_ = explode(n);
            // console.info(`EXPL ${JSON.stringify(n)} → ${JSON.stringify(n_)}`)
            n = n_
            continue
        }

        const splitnumContanier = {pair: null, index: -1}
        findContainer(splitnumContanier, x => (Number.isInteger(x) && x > 9), n)

        if (splitnumContanier.pair !== null) {
            // const snap0 = JSON.stringify(splitnumContanier.pair[splitnumContanier.index]);
            // const snap1 = JSON.stringify(n);

            splitnumContanier.pair[splitnumContanier.index] = split_number(
                splitnumContanier.pair[splitnumContanier.index]
            )

            // console.info(`SPLT ${snap0} ${snap1} → ${JSON.stringify(n)}`)
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

function explode(src) {
    const n = clone(src)

    const explodingBox = {value: null}
    findExploding(explodingBox, 0, n)
    assert(explodingBox.value !== null)

    // console.info(`Exploding the ${JSON.stringify(explodingBox.value)}`)

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

    explodingPairContanier.pair[explodingPairContanier.index] = 0

    if (lneiContanier.pair !== null) {
        lneiContanier.pair[lneiContanier.index] += A
    }

    if (rneiContanier.pair !== null) {
        rneiContanier.pair[rneiContanier.index] += B
    }

    return n
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
