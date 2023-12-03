fun bruteForce(xs: List<Int>): Int {
    val fs = mutableMapOf<Int, Int>()
    for (x in xs) {
        fs.put(x, fs.getOrDefault(x, 0) + 1)
    }

    val ys = fs.keys
    var result = 0

    fun recur(i: Int, acc: Set<Int>): Unit {
        val k = ys.elementAt(i)
        val f = fs[k]!!

        run {
            val acc_ = acc + k
            if (i == ys.size - 1) {
                result = maxOf(result, acc_.size)
            } else {
                recur(i + 1, acc_)
            }
        }

        run {
            val acc_ = acc + (if (f > 1) setOf(k, k + 1) else setOf(k + 1))
            if (i == ys.size - 1) {
                result = maxOf(result, acc_.size)
            } else {
                recur(i + 1, acc_)
            }
        }

        if (k > 1) {
            val acc_ = acc + (if (f > 1) setOf(k, k - 1) else setOf(k - 1))
            if (i == ys.size - 1) {
                result = maxOf(result, acc_.size)
            } else {
                recur(i + 1, acc_)
            }
        }

        if (k > 1 && f > 1) {
            val acc_ = acc + (if (f == 2) setOf(k - 1, k + 1) else setOf(k - 1, k, k + 1))
            if (i == ys.size - 1) {
                result = maxOf(result, acc_.size)
            } else {
                recur(i + 1, acc_)
            }
        }
    }
    recur(0, setOf())
    return result
}

fun main() {
    val n = readInt()
    val xs = readInts()
    assert(xs.size == n)

    val fs = Array<Int>(Hi + 1) { 0 }
    for (x in xs) {
        if (fs[x] < 3) fs[x]++
    }

    val no = Array<Int>(Hi + 1) { 0 }
    val up = Array<Int>(Hi + 1) { 0 }
    val dn = Array<Int>(Hi + 1) { 0 }
    val bo = Array<Int>(Hi + 1) { 0 }

    no[1] = if (fs[1] > 0) 1 else 0
    up[1] = if (fs[1] > 1) 2 else 1

    for (i in 2..Hi) {
        if (fs[i] == 0) {
            no[i] = maxOf(no[i - 1], up[i - 1], dn[i - 1], bo[i - 1])
            continue
        }

        if (fs[i - 1] == 0) {
            no[i] = no[i - 1] + 1
            up[i] = no[i - 1] + (if (fs[i] == 1) 1 else 2)
            dn[i] = no[i - 1] + (if (fs[i] == 1) 1 else 2)
            if (fs[i] >= 2) {
                bo[i] = no[i - 1] + fs[i]
            }
            continue
        }

        no[i] = maxOf(no[i - 1] + 1, up[i - 1], dn[i - 1] + 1)
        if (bo[i - 1] > 0) {
            no[i] = maxOf(no[i], bo[i - 1])
        }

        up[i] = no[i - 1] + (if (fs[i] == 1) 1 else 2)
        if (up[i - 1] > 0) {
            up[i] = maxOf(up[i], up[i - 1] + 1)
        }
        if (dn[i - 1] > 0) {
            up[i] = maxOf(up[i], dn[i - 1] + (if (fs[i] == 1) 1 else 2))
        }
        if (bo[i - 1] > 0) {
            up[i] = maxOf(up[i], bo[i - 1] + 1)
        }

        dn[i] = no[i - 1] + (if (fs[i] == 1) 0 else 1)
        if (up[i - 1] > 0) {
            dn[i] = maxOf(dn[i], up[i - 1] + (if (fs[i - 1] == 1) 1 else 0))
        }
        if (dn[i - 1] > 0) {
            dn[i] =
                    maxOf(
                            dn[i],
                            dn[i - 1] +
                                    when (fs[i - 1] to fs[i]) {
                                        1 to 1 -> 1
                                        1 to 2 -> 2
                                        1 to 3 -> 2
                                        2 to 1 -> 0
                                        2 to 2 -> 1
                                        2 to 3 -> 1
                                        3 to 1 -> 0
                                        3 to 2 -> 1
                                        else -> 1 // 3 to 3
                                    }
                    )
        }
        if (bo[i - 1] > 0) {
            assert(fs[i - 1] >= 2)
            dn[i] =
                    maxOf(
                            dn[i],
                            bo[i - 1] +
                                    when (fs[i - 1] to fs[i]) {
                                        2 to 1 -> 1
                                        2 to 2 -> 1
                                        2 to 3 -> 1
                                        3 to 1 -> 0
                                        3 to 2 -> 0
                                        else -> 0 // 3 to 3
                                    }
                    )
        }

        if (fs[i] < 2) continue
        bo[i] = no[i - 1] + (if (fs[i] == 2) 1 else 2)
        if (up[i - 1] > 0) {
            bo[i] =
                    maxOf(
                            bo[i],
                            up[i - 1] +
                                    when (fs[i - 1] to fs[i]) {
                                        1 to 2 -> 2
                                        1 to 3 -> 2
                                        2 to 2 -> 1
                                        2 to 3 -> 1
                                        3 to 2 -> 1
                                        else -> 1 // 3 to 3
                                    }
                    )
        }
        if (dn[i - 1] > 0) {
            bo[i] = maxOf(bo[i], dn[i - 1] + (if (fs[i - 1] == 1) fs[i] else (fs[i] - 1)))
        }
        if (bo[i - 1] > 0) {
            bo[i] =
                    maxOf(
                            bo[i],
                            bo[i - 1] +
                                    when (fs[i - 1] to fs[i]) {
                                        2 to 2 -> 2
                                        2 to 3 -> 2
                                        3 to 2 -> 1
                                        else -> 1 // 3 to 3
                                    }
                    )
        }
    }

    println(maxOf(no.last(), up.last(), dn.last(), bo.last()))
}

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map(String::toInt)

private const val Hi: Int = 150001
