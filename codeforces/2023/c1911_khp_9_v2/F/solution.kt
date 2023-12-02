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
    dn[1] = 0
    bo[1] = 0

    for (i in 2..Hi) {
        val pre = maxOf(no[i - 1], up[i - 1], dn[i - 1], bo[i - 1])

        if (fs[i] == 0) {
            no[i] = pre
            continue
        }

        if (fs[i - 1] == 0) {
            no[i] = pre + 1
            up[i] = pre + (if (fs[i] == 1) 1 else 2)
            dn[i] = pre + (if (fs[i] == 1) 1 else 2)
            if (fs[i] == 3) {
                bo[i] = pre + 3
            }
            continue
        }

        // no[i] = TODO()
        // up[i] = TODO()
        // dn[i] = TODO()
        // bo[i] = TODO()
    }

    println(maxOf(no.last(), up.last(), dn.last(), bo.last()))
}

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map(String::toInt)

private const val Hi: Int = 150001
