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

    for (i in 1..Hi) {
        no[i] = no[i - 1] + (if (fs[i] > 0) 1 else 0)
        if (fs[i - 1] > 0) {
            no[i] = maxOf(no[i], up[i - 1])
        } else {
            no[i] = maxOf(no[i], up[i - 1] + (if (fs[i] > 0) 1 else 0))
        }

        up[i] = TODO()
        dn[i] = TODO()
        bo[i] = TODO()
    }

    println(maxOf(no.last(), up.last(), dn.last(), bo.last()))
}

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map(String::toInt)

private const val Hi: Int = 150001
