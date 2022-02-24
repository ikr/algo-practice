fun decode(xs : String) : String {
    var i = 0
    var d = 1
    val result = mutableListOf<Char>()

    while (i < xs.length) {
        result.add(xs[i])
        i += d
        ++d
    }

    return result.joinToString("")
}

fun main() {
    val n = readInt()
    val xs = readLn()
    assert(xs.length == n)
    println(decode(xs))
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
