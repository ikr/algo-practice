fun main() {
    repeat(readInt()) {
        val (n, k) = readInts()
        val s = readLn()
        println("($n, $k) $s")
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
