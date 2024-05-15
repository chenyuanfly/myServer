let uploadPaused = false; // 控制变量，初始为false，表示上传未暂停
let currentChunk = 0; // 当前上传的块索引
let totalChunks = 0; // 总块数
let file = null; // 用户选择的文件
let progressBar = document.getElementById('progressBar');
var chunkSize = 1 * 1024; // 设置为1KB的块

document.getElementById('uploadButton').addEventListener('click', async function() {
    var fileInput = document.getElementById('fileInput');
    file = fileInput.files[0];
    if (!file) return;

    currentChunk = 0;
    totalChunks = Math.ceil(file.size / chunkSize);

    console.log("totalChunks:" + totalChunks);

    this.disabled = true; // 禁用上传按钮
    document.getElementById('pauseButton').disabled = false; // 启用暂停按钮
    uploadPaused = true;

    if (uploadPaused) {
        uploadPaused = false; // 如果之前暂停了，点击上传按钮继续上传
        uploadNextChunk();
    }
});

document.getElementById('pauseButton').addEventListener('click', function() {
    if (uploadPaused) {
        // 如果上传已暂停，再次点击暂停按钮则继续上传
        this.textContent = '暂停上传';
        uploadPaused = false;
        uploadNextChunk();
    } else {
        // 点击暂停按钮暂停上传
        this.textContent = '继续上传';
        uploadPaused = true;
    }
});

async function readAsArrayBuffer(sliceStart, sliceEnd) {
    return new Promise((resolve, reject) => {
        const chunk = file.slice(sliceStart, sliceEnd);
        const fileReader = new FileReader();
        fileReader.onload = () => resolve(fileReader.result);
        fileReader.onerror = reject;
        fileReader.readAsArrayBuffer(chunk);
    });
}

async function uploadNextChunk() {
    if (uploadPaused) return; // 如果上传已暂停，则不执行上传逻辑

    var start = currentChunk * chunkSize;
    var end = Math.min(start + chunkSize, file.size);
    var chunk = await readAsArrayBuffer(start, end);
    var formData = new FormData();
    formData.append('file', new Blob([chunk]));
    formData.append('currentChunk', currentChunk + 1);
    formData.append('totalChunks', totalChunks);

    try {
        var response = await fetch('/', {
            method: 'POST',
            body: formData
        });
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        currentChunk++;
        var percentComplete = ((currentChunk / totalChunks) * 100).toFixed(2);
        progressBar.style.width = percentComplete + '%';
        progressBar.setAttribute('aria-valuenow', percentComplete);

        if (currentChunk < totalChunks) {
            uploadNextChunk(); // 继续上传下一块
        } else {
            alert('文件上传完成！');
            document.getElementById('uploadButton').disabled = false;
            document.getElementById('pauseButton').disabled = true;
        }
    } catch (error) {
        console.error('上传失败:', error);
    }
}

document.getElementById('fileInput').addEventListener('change', function() {
    document.getElementById('uploadButton').disabled = false;
    document.getElementById('pauseButton').disabled = true; // 初始禁用暂停按钮
});