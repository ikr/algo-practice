fun main() {
    val n = readInt()
    val xs = readInts()
    assert(xs.size == n)

    val fs = Array<Int>(Hi + 1) { 0 }
    for (x in xs) {
        if (fs[x] < 3) fs[x]++
    }

    val up = Array<Int>(Hi + 1) { 0 }
    val dn = Array<Int>(Hi + 1) { 0 }
    val bo = Array<Int>(Hi + 1) { 0 }
}

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map(String::toInt)

private const val Hi: Int = 150001
