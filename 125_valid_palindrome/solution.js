/**
 * @param {string} s
 * @return {boolean}
 */
var isPalindrome = function(s) {
    let clean = s.replace(/[\W_]+/g,"").toLowerCase()
    let r=clean.length-1
    for(let i=0;i<clean.length;i++){
        if(clean[i]!==clean[r]) return false
        r--
    }
    return true
};