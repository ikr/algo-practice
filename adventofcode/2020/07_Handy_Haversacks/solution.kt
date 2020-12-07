fun main() {
    val aggs = generateSequence(::readLine).map(::parseLine).toList()
    val g = gather_graph(aggs)

    val ans = aggs.map { it.color }.count {
        contains_recur(g, "shiny gold", it)
    }

    println(ans)
}

private fun contains_recur(g: Map<String, List<String>>, needle: String, u: String): Boolean {
    if (!g.containsKey(u)) return false

    for (v in g[u]!!) {
        if (v == needle) return true
        if (contains_recur(g, needle, v)) return true
    }

    return false
}

private fun gather_graph(aggs: List<Agg>): Map<String, List<String>> {
    val ans = mutableMapOf<String, List<String>>()

    for ((color, subs) in aggs) {
        val adj = subs.map { it.color }
        ans[color] = adj
    }

    return ans
}

private fun parseLine(line: String): Agg {
    if (line.endsWith(" bags contain no other bags.")) {
        return Agg(line.split(" bags ").first(), emptyList())
    }

    val g = Regex("^([a-z ]+) bags contain ([0-9a-z, ]+)\\.$").matchEntire(line)!!.groups
    val color = g[1]!!.value
    val subs = g[2]!!.value.split(", ").map(::parseSubText)

    return Agg(color, subs)
}

private fun parseSubText(text: String): Sub {
    val g = Regex("^(\\d+) ([a-z ]+) bag(s?)$").matchEntire(text)!!.groups
    return Sub(g[1]!!.value.toInt(), g[2]!!.value)
}

private data class Agg(val color: String, val subs: List<Sub>)
private data class Sub(val count: Int, val color: String)

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
